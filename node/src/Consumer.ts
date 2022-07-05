import { Logger } from './Logger';
import { EnhancedEventEmitter } from './EnhancedEventEmitter';
import { Channel } from './Channel';
import { PayloadChannel } from './PayloadChannel';
import { ProducerStat } from './Producer';
import {
	MediaKind,
	RtpCapabilities,
	RtpParameters
} from './RtpParameters';

export type ConsumerOptions =
{
	/**
	 * The id of the Producer to consume.
	 */
	producerId: string;

	/**
	 * RTP capabilities of the consuming endpoint.
	 */
	rtpCapabilities: RtpCapabilities;

	/**
	 * Whether the Consumer must start in paused mode. Default false.
	 *
	 * When creating a video Consumer, it's recommended to set paused to true,
	 * then transmit the Consumer parameters to the consuming endpoint and, once
	 * the consuming endpoint has created its local side Consumer, unpause the
	 * server side Consumer using the resume() method. This is an optimization
	 * to make it possible for the consuming endpoint to render the video as far
	 * as possible. If the server side Consumer was created with paused: false,
	 * mediasoup will immediately request a key frame to the remote Producer and
	 * suych a key frame may reach the consuming endpoint even before it's ready
	 * to consume it, generating “black” video until the device requests a keyframe
	 * by itself.
	 */
	paused?: boolean;

	/**
	 * The MID for the Consumer. If not specified, a sequentially growing
	 * number will be assigned.
	 */
	mid?: string;

	/**
	 * Preferred spatial and temporal layer for simulcast or SVC media sources.
	 * If unset, the highest ones are selected.
	 */
	preferredLayers?: ConsumerLayers;

	/**
	 * Whether this Consumer should ignore DTX packets (only valid for Opus codec).
	 * If set, DTX packets are not forwarded to the remote Consumer.
	 */
	ignoreDtx?: Boolean;

	/**
	 * Whether this Consumer should consume all RTP streams generated by the
	 * Producer.
	 */
	pipe?: boolean;

	/**
	 * Custom application data.
	 */
	appData?: Record<string, unknown>;
}

/**
 * Valid types for 'trace' event.
 */
export type ConsumerTraceEventType = 'rtp' | 'keyframe' | 'nack' | 'pli' | 'fir';

/**
 * 'trace' event data.
 */
export type ConsumerTraceEventData =
{
	/**
	 * Trace type.
	 */
	type: ConsumerTraceEventType;

	/**
	 * Event timestamp.
	 */
	timestamp: number;

	/**
	 * Event direction.
	 */
	direction: 'in' | 'out';

	/**
	 * Per type information.
	 */
	info: any;
}

export type ConsumerScore =
{
	/**
	 * The score of the RTP stream of the consumer.
	 */
	score: number;

	/**
	 * The score of the currently selected RTP stream of the producer.
	 */
	producerScore: number;

	/**
	 * The scores of all RTP streams in the producer ordered by encoding (just
	 * useful when the producer uses simulcast).
	 */
	producerScores: number[];
}

export type ConsumerLayers =
{
	/**
	 * The spatial layer index (from 0 to N).
	 */
	spatialLayer: number;

	/**
	 * The temporal layer index (from 0 to N).
	 */
	temporalLayer?: number;
}

export type ConsumerStat =
{
	// Common to all RtpStreams.
	type: string;
	timestamp: number;
	ssrc: number;
	rtxSsrc?: number;
	kind: string;
	mimeType: string;
	packetsLost: number;
	fractionLost: number;
	packetsDiscarded: number;
	packetsRetransmitted: number;
	packetsRepaired: number;
	nackCount: number;
	nackPacketCount: number;
	pliCount: number;
	firCount: number;
	score: number;
	packetCount: number;
	byteCount: number;
	bitrate: number;
	roundTripTime?: number;
}

/**
 * Consumer type.
 */
export type ConsumerType = 'simple' | 'simulcast' | 'svc' | 'pipe';

export type ConsumerEvents =
{ 
	transportclose: [];
	producerclose: [];
	producerpause: [];
	producerresume: [];
	score: [ConsumerScore];
	layerschange: [ConsumerLayers?];
	trace: [ConsumerTraceEventData];
	rtp: [Buffer];
	// Private events.
	'@close': [];
	'@producerclose': [];
}

export type ConsumerObserverEvents =
{
	close: [];
	pause: [];
	resume: [];
	score: [ConsumerScore];
	layerschange: [ConsumerLayers?];
	trace: [ConsumerTraceEventData];
}

const logger = new Logger('Consumer');

export class Consumer extends EnhancedEventEmitter<ConsumerEvents>
{
	// Internal data.
	readonly #internal:
	{
		routerId: string;
		transportId: string;
		consumerId: string;
	};

	// Consumer data.
	readonly #data:
	{
		producerId: string;
		kind: MediaKind;
		rtpParameters: RtpParameters;
		type: ConsumerType;
	};

	// Channel instance.
	readonly #channel: Channel;

	// PayloadChannel instance.
	#payloadChannel: PayloadChannel;

	// Closed flag.
	#closed = false;

	// Custom app data.
	readonly #appData: Record<string, unknown>;

	// Paused flag.
	#paused = false;

	// Associated Producer paused flag.
	#producerPaused = false;

	// Current priority.
	#priority = 1;

	// Current score.
	#score: ConsumerScore;

	// Preferred layers.
	#preferredLayers?: ConsumerLayers;

	// Curent layers.
	#currentLayers?: ConsumerLayers;

	// Observer instance.
	readonly #observer = new EnhancedEventEmitter<ConsumerObserverEvents>();

	/**
	 * @private
	 */
	constructor(
		{
			internal,
			data,
			channel,
			payloadChannel,
			appData,
			paused,
			producerPaused,
			score = { score: 10, producerScore: 10, producerScores: [] },
			preferredLayers
		}:
		{
			internal: any;
			data: any;
			channel: Channel;
			payloadChannel: PayloadChannel;
			appData?: Record<string, unknown>;
			paused: boolean;
			producerPaused: boolean;
			score?: ConsumerScore;
			preferredLayers?: ConsumerLayers;
		})
	{
		super();

		logger.debug('constructor()');

		this.#internal = internal;
		this.#data = data;
		this.#channel = channel;
		this.#payloadChannel = payloadChannel;
		this.#appData = appData || {};
		this.#paused = paused;
		this.#producerPaused = producerPaused;
		this.#score = score;
		this.#preferredLayers = preferredLayers;

		this.handleWorkerNotifications();
	}

	/**
	 * Consumer id.
	 */
	get id(): string
	{
		return this.#internal.consumerId;
	}

	/**
	 * Associated Producer id.
	 */
	get producerId(): string
	{
		return this.#data.producerId;
	}

	/**
	 * Whether the Consumer is closed.
	 */
	get closed(): boolean
	{
		return this.#closed;
	}

	/**
	 * Media kind.
	 */
	get kind(): MediaKind
	{
		return this.#data.kind;
	}

	/**
	 * RTP parameters.
	 */
	get rtpParameters(): RtpParameters
	{
		return this.#data.rtpParameters;
	}

	/**
	 * Consumer type.
	 */
	get type(): ConsumerType
	{
		return this.#data.type;
	}

	/**
	 * Whether the Consumer is paused.
	 */
	get paused(): boolean
	{
		return this.#paused;
	}

	/**
	 * Whether the associate Producer is paused.
	 */
	get producerPaused(): boolean
	{
		return this.#producerPaused;
	}

	/**
	 * Current priority.
	 */
	get priority(): number
	{
		return this.#priority;
	}

	/**
	 * Consumer score.
	 */
	get score(): ConsumerScore
	{
		return this.#score;
	}

	/**
	 * Preferred video layers.
	 */
	get preferredLayers(): ConsumerLayers | undefined
	{
		return this.#preferredLayers;
	}

	/**
	 * Current video layers.
	 */
	get currentLayers(): ConsumerLayers | undefined
	{
		return this.#currentLayers;
	}

	/**
	 * App custom data.
	 */
	get appData(): Record<string, unknown>
	{
		return this.#appData;
	}

	/**
	 * Invalid setter.
	 */
	set appData(appData: Record<string, unknown>) // eslint-disable-line no-unused-vars
	{
		throw new Error('cannot override appData object');
	}

	/**
	 * Observer.
	 */
	get observer(): EnhancedEventEmitter<ConsumerObserverEvents>
	{
		return this.#observer;
	}

	/**
	 * @private
	 * Just for testing purposes.
	 */
	get channelForTesting(): Channel
	{
		return this.#channel;
	}

	/**
	 * Close the Consumer.
	 */
	close(): void
	{
		if (this.#closed)
			return;

		logger.debug('close()');

		this.#closed = true;

		// Remove notification subscriptions.
		this.#channel.removeAllListeners(this.#internal.consumerId);
		this.#payloadChannel.removeAllListeners(this.#internal.consumerId);

		this.#channel.request('consumer.close', this.#internal)
			.catch(() => {});

		this.emit('@close');

		// Emit observer event.
		this.#observer.safeEmit('close');
	}

	/**
	 * Transport was closed.
	 *
	 * @private
	 */
	transportClosed(): void
	{
		if (this.#closed)
			return;

		logger.debug('transportClosed()');

		this.#closed = true;

		// Remove notification subscriptions.
		this.#channel.removeAllListeners(this.#internal.consumerId);
		this.#payloadChannel.removeAllListeners(this.#internal.consumerId);

		this.safeEmit('transportclose');

		// Emit observer event.
		this.#observer.safeEmit('close');
	}

	/**
	 * Dump Consumer.
	 */
	async dump(): Promise<any>
	{
		logger.debug('dump()');

		return this.#channel.request('consumer.dump', this.#internal);
	}

	/**
	 * Get Consumer stats.
	 */
	async getStats(): Promise<Array<ConsumerStat | ProducerStat>>
	{
		logger.debug('getStats()');

		return this.#channel.request('consumer.getStats', this.#internal);
	}

	/**
	 * Pause the Consumer.
	 */
	async pause(): Promise<void>
	{
		logger.debug('pause()');

		const wasPaused = this.#paused || this.#producerPaused;

		await this.#channel.request('consumer.pause', this.#internal);

		this.#paused = true;

		// Emit observer event.
		if (!wasPaused)
			this.#observer.safeEmit('pause');
	}

	/**
	 * Resume the Consumer.
	 */
	async resume(): Promise<void>
	{
		logger.debug('resume()');

		const wasPaused = this.#paused || this.#producerPaused;

		await this.#channel.request('consumer.resume', this.#internal);

		this.#paused = false;

		// Emit observer event.
		if (wasPaused && !this.#producerPaused)
			this.#observer.safeEmit('resume');
	}

	/**
	 * Set preferred video layers.
	 */
	async setPreferredLayers(
		{
			spatialLayer,
			temporalLayer
		}: ConsumerLayers
	): Promise<void>
	{
		logger.debug('setPreferredLayers()');

		const reqData = { spatialLayer, temporalLayer };

		const data = await this.#channel.request(
			'consumer.setPreferredLayers', this.#internal, reqData);

		this.#preferredLayers = data || undefined;
	}

	/**
	 * Set priority.
	 */
	async setPriority(priority: number): Promise<void>
	{
		logger.debug('setPriority()');

		const reqData = { priority };

		const data = await this.#channel.request(
			'consumer.setPriority', this.#internal, reqData);

		this.#priority = data.priority;
	}

	/**
	 * Unset priority.
	 */
	async unsetPriority(): Promise<void>
	{
		logger.debug('unsetPriority()');

		const reqData = { priority: 1 };

		const data = await this.#channel.request(
			'consumer.setPriority', this.#internal, reqData);

		this.#priority = data.priority;
	}

	/**
	 * Request a key frame to the Producer.
	 */
	async requestKeyFrame(): Promise<void>
	{
		logger.debug('requestKeyFrame()');

		await this.#channel.request('consumer.requestKeyFrame', this.#internal);
	}

	/**
	 * Enable 'trace' event.
	 */
	async enableTraceEvent(types: ConsumerTraceEventType[] = []): Promise<void>
	{
		logger.debug('enableTraceEvent()');

		const reqData = { types };

		await this.#channel.request(
			'consumer.enableTraceEvent', this.#internal, reqData);
	}

	private handleWorkerNotifications(): void
	{
		this.#channel.on(this.#internal.consumerId, (event: string, data?: any) =>
		{
			switch (event)
			{
				case 'producerclose':
				{
					if (this.#closed)
						break;

					this.#closed = true;

					// Remove notification subscriptions.
					this.#channel.removeAllListeners(this.#internal.consumerId);
					this.#payloadChannel.removeAllListeners(this.#internal.consumerId);

					this.emit('@producerclose');
					this.safeEmit('producerclose');

					// Emit observer event.
					this.#observer.safeEmit('close');

					break;
				}

				case 'producerpause':
				{
					if (this.#producerPaused)
						break;

					const wasPaused = this.#paused || this.#producerPaused;

					this.#producerPaused = true;

					this.safeEmit('producerpause');

					// Emit observer event.
					if (!wasPaused)
						this.#observer.safeEmit('pause');

					break;
				}

				case 'producerresume':
				{
					if (!this.#producerPaused)
						break;

					const wasPaused = this.#paused || this.#producerPaused;

					this.#producerPaused = false;

					this.safeEmit('producerresume');

					// Emit observer event.
					if (wasPaused && !this.#paused)
						this.#observer.safeEmit('resume');

					break;
				}

				case 'score':
				{
					const score = data as ConsumerScore;

					this.#score = score;

					this.safeEmit('score', score);

					// Emit observer event.
					this.#observer.safeEmit('score', score);

					break;
				}

				case 'layerschange':
				{
					const layers = data as ConsumerLayers | undefined;

					this.#currentLayers = layers;

					this.safeEmit('layerschange', layers);

					// Emit observer event.
					this.#observer.safeEmit('layerschange', layers);

					break;
				}

				case 'trace':
				{
					const trace = data as ConsumerTraceEventData;

					this.safeEmit('trace', trace);

					// Emit observer event.
					this.#observer.safeEmit('trace', trace);

					break;
				}

				default:
				{
					logger.error('ignoring unknown event "%s"', event);
				}
			}
		});

		this.#payloadChannel.on(
			this.#internal.consumerId,
			(event: string, data: any | undefined, payload: Buffer) =>
			{
				switch (event)
				{
					case 'rtp':
					{
						if (this.#closed)
							break;

						const packet = payload;

						this.safeEmit('rtp', packet);

						break;
					}

					default:
					{
						logger.error('ignoring unknown event "%s"', event);
					}
				}
			});
	}
}
