#define MS_CLASS "RTC::Codecs::AV1X"
// #define MS_LOG_DEV_LEVEL 3

#include "RTC/Codecs/AV1X.hpp"
#include "Logger.hpp"

enum ObuTypes {
	OBU_SEQUENCE_HEADER 		= 1,
	OBU_TEMPORAL_DELIMITER 		= 2,
	OBU_FRAME_HEADER 			= 3,
	OBU_TILE_GROUP 				= 4,
	OBU_METADATA 				= 5,
	OBU_FRAME 					= 6,
	OBU_REDUNDANT_FRAME_HEADER 	= 7,
	OBU_TILE_LIST 				= 8,
	OBU_PADDING 				= 15
};

namespace RTC
{
	namespace Codecs
	{
		/* Class methods. */

		AV1X::PayloadDescriptor* AV1X::Parse(
		  const uint8_t* data,
		  size_t len,
		  RTC::RtpPacket::FrameMarking* /*frameMarking*/,
		  uint8_t /*frameMarkingLen*/)
		{
			MS_TRACE();

			if (len < 1)
				return nullptr;

			std::unique_ptr<PayloadDescriptor> payloadDescriptor(new PayloadDescriptor());

			uint32_t bitOffset{ 0 };

			// AV1 Aggregation Header (https://aomediacodec.github.io/av1-rtp-spec/#44-av1-aggregation-header)
			payloadDescriptor->z = Utils::Bits::ReadBits(data, len, 1, bitOffset);
			payloadDescriptor->y = Utils::Bits::ReadBits(data, len, 1, bitOffset);
			payloadDescriptor->w = Utils::Bits::ReadBits(data, len, 2, bitOffset);
			payloadDescriptor->n = Utils::Bits::ReadBits(data, len, 1, bitOffset);
			bitOffset += 3;

			// continuation of an OBU fragment
			if (payloadDescriptor->z == 1)
			{
				return payloadDescriptor.release();
			}

			// https://aomediacodec.github.io/av1-spec/av1-spec.pdf 5.3.1
			if (payloadDescriptor->n)
			{
				MS_DUMP("<av1-aggregation-header> z=%u y=%u w=%u n=%u",
					payloadDescriptor->z, payloadDescriptor->y, payloadDescriptor->w, payloadDescriptor->n
				);
				payloadDescriptor->isKeyFrame = true;
			}

			// If set to 0, each OBU element MUST be preceded by a length field.
			if (payloadDescriptor->w == 0) {
				Utils::Bits::ReadBitsLeb128(data, len, bitOffset);		
			}

			// https://aomediacodec.github.io/av1-spec/#obu-header-syntax
			bitOffset += 1;
			payloadDescriptor->obu_type = Utils::Bits::ReadBits(data, len, 4, bitOffset);
			payloadDescriptor->obu_extension_flag = Utils::Bits::ReadBits(data, len, 1, bitOffset);
			payloadDescriptor->obu_has_size_field = Utils::Bits::ReadBits(data, len, 1, bitOffset);
			bitOffset += 1;
			
			// https://aomediacodec.github.io/av1-spec/#obu-extension-header-syntax
			if (payloadDescriptor->obu_extension_flag)
			{
				payloadDescriptor->tlIndex = Utils::Bits::ReadBits(data, len, 3, bitOffset);
				payloadDescriptor->hasTlIndex = true;
				payloadDescriptor->slIndex = Utils::Bits::ReadBits(data, len, 2, bitOffset);
				payloadDescriptor->hasSlIndex = true;
				bitOffset += 3;
			}

			if (payloadDescriptor->obu_has_size_field)
			{
				payloadDescriptor->obu_size = Utils::Bits::ReadBitsLeb128(data, len, bitOffset);
			}
			else
			{
        		// payloadDescriptor->obu_size = sz - 1 - payloadDescriptor->obu_extension_flag	 
    		}

			/* {
				MS_DUMP("<av1-aggregation-header> z=%u y=%u w=%u n=%u",
					payloadDescriptor->z, payloadDescriptor->y, payloadDescriptor->w, payloadDescriptor->n
				);
				MS_DUMP(
					"<av1-obu-header>"
					" obu_type=%u"
					" obu_extension_flag=%u"
					" obu_has_size_field=%u"
					" obu_size=%u"
					" slIndex=%u"
					" tlIndex=%u"
					,
					payloadDescriptor->obu_type, 
					payloadDescriptor->obu_extension_flag, 
					payloadDescriptor->obu_has_size_field, 
					payloadDescriptor->obu_size,
					payloadDescriptor->slIndex, 
					payloadDescriptor->tlIndex
				);
			} */


			if (
				payloadDescriptor->obu_type != OBU_SEQUENCE_HEADER &&
				payloadDescriptor->obu_type != OBU_TEMPORAL_DELIMITER &&
				payloadDescriptor->obu_extension_flag == 1
			) 
			{
				
			}

			// 5.5.1.
			if (payloadDescriptor->obu_type == OBU_SEQUENCE_HEADER)
			{
				

			}
			else if (payloadDescriptor->obu_type == OBU_FRAME_HEADER || 
					 payloadDescriptor->obu_type == OBU_REDUNDANT_FRAME_HEADER)
			{



			}

			return payloadDescriptor.release();
		}

		void AV1X::ProcessRtpPacket(RTC::RtpPacket* packet)
		{
			MS_TRACE();

			auto* data = packet->GetPayload();
			auto len   = packet->GetPayloadLength();
			RtpPacket::FrameMarking* frameMarking{ nullptr };
			uint8_t frameMarkingLen{ 0 };
			
			// Read frame-marking.
			packet->ReadFrameMarking(&frameMarking, frameMarkingLen);

			PayloadDescriptor* payloadDescriptor = AV1X::Parse(data, len, frameMarking, frameMarkingLen);

			if (!payloadDescriptor)
				return;

			if (payloadDescriptor->isKeyFrame)
			{
				MS_DEBUG_DEV(
				  "key frame [spatialLayer:%" PRIu8 ", temporalLayer:%" PRIu8 "]",
				  packet->GetSpatialLayer(),
				  packet->GetTemporalLayer());
			}

			auto* payloadDescriptorHandler = new PayloadDescriptorHandler(payloadDescriptor);

			packet->SetPayloadDescriptorHandler(payloadDescriptorHandler);
		}

		/* Instance methods. */

		void AV1X::PayloadDescriptor::Dump() const
		{
			MS_TRACE();

			MS_DUMP("<PayloadDescriptor>");
			MS_DUMP(
			  "  i:%" PRIu8 "|p:%" PRIu8 "|l:%" PRIu8 "|f:%" PRIu8 "|b:%" PRIu8 "|e:%" PRIu8 "|v:%" PRIu8,
			  this->i,
			  this->p,
			  this->l,
			  this->f,
			  this->b,
			  this->e,
			  this->v);
			MS_DUMP("  pictureId            : %" PRIu16, this->pictureId);
			MS_DUMP("  slIndex              : %" PRIu8, this->slIndex);
			MS_DUMP("  tlIndex              : %" PRIu8, this->tlIndex);
			MS_DUMP("  tl0PictureIndex      : %" PRIu8, this->tl0PictureIndex);
			MS_DUMP("  interLayerDependency : %" PRIu8, this->interLayerDependency);
			MS_DUMP("  switchingUpPoint     : %" PRIu8, this->switchingUpPoint);
			MS_DUMP("  isKeyFrame           : %s", this->isKeyFrame ? "true" : "false");
			MS_DUMP("  hasPictureId         : %s", this->hasPictureId ? "true" : "false");
			MS_DUMP("  hasOneBytePictureId  : %s", this->hasOneBytePictureId ? "true" : "false");
			MS_DUMP("  hasTwoBytesPictureId : %s", this->hasTwoBytesPictureId ? "true" : "false");
			MS_DUMP("  hasTl0PictureIndex   : %s", this->hasTl0PictureIndex ? "true" : "false");
			MS_DUMP("  hasSlIndex           : %s", this->hasSlIndex ? "true" : "false");
			MS_DUMP("  hasTlIndex           : %s", this->hasTlIndex ? "true" : "false");
			MS_DUMP("</PayloadDescriptor>");
		}

		AV1X::PayloadDescriptorHandler::PayloadDescriptorHandler(AV1X::PayloadDescriptor* payloadDescriptor)
		{
			MS_TRACE();

			this->payloadDescriptor.reset(payloadDescriptor);
		}

		bool AV1X::PayloadDescriptorHandler::Process(
		  RTC::Codecs::EncodingContext* encodingContext, uint8_t* /*data*/, bool& marker)
		{
			MS_TRACE();

			auto* context = static_cast<RTC::Codecs::AV1X::EncodingContext*>(encodingContext);

			MS_ASSERT(context->GetTargetSpatialLayer() >= 0, "target spatial layer cannot be -1");
			MS_ASSERT(context->GetTargetTemporalLayer() >= 0, "target temporal layer cannot be -1");

			auto packetSpatialLayer  = GetSpatialLayer();
			auto packetTemporalLayer = GetTemporalLayer();
			auto tmpSpatialLayer     = context->GetCurrentSpatialLayer();
			auto tmpTemporalLayer    = context->GetCurrentTemporalLayer();

			// If packet spatial or temporal layer is higher than maximum announced
			// one, drop the packet.
			// clang-format off
			if (
				packetSpatialLayer >= context->GetSpatialLayers() ||
				packetTemporalLayer >= context->GetTemporalLayers()
			)
			// clang-format on
			{
				MS_WARN_TAG(
				  rtp, "too high packet layers %" PRIu8 ":%" PRIu8, packetSpatialLayer, packetTemporalLayer);

				return false;
			}

			// Check whether pictureId sync is required.
			// clang-format off
			if (
				context->syncRequired &&
				this->payloadDescriptor->hasPictureId
			)
			// clang-format on
			{
				context->pictureIdManager.Sync(this->payloadDescriptor->pictureId - 1);

				context->syncRequired = false;
			}

			// clang-format off
			bool isOldPacket = (
				this->payloadDescriptor->hasPictureId &&
				RTC::SeqManager<uint16_t>::IsSeqLowerThan(
					this->payloadDescriptor->pictureId,
					context->pictureIdManager.GetMaxInput())
			);
			// clang-format on

			// Upgrade current spatial layer if needed.
			if (context->GetTargetSpatialLayer() > context->GetCurrentSpatialLayer())
			{
				if (this->payloadDescriptor->isKeyFrame)
				{
					MS_DEBUG_DEV(
					  "upgrading tmpSpatialLayer from %" PRIu16 " to %" PRIu16 " (packet:%" PRIu8 ":%" PRIu8
					  ")",
					  context->GetCurrentSpatialLayer(),
					  context->GetTargetSpatialLayer(),
					  packetSpatialLayer,
					  packetTemporalLayer);

					tmpSpatialLayer  = context->GetTargetSpatialLayer();
					//tmpTemporalLayer = 0; // Just in case.
				}
			}
			// Downgrade current spatial layer if needed.
			else if (context->GetTargetSpatialLayer() < context->GetCurrentSpatialLayer())
			{
				// In K-SVC we must wait for a keyframe.
				if (context->IsKSvc())
				{
					if (this->payloadDescriptor->isKeyFrame)
					// clang-format on
					{
						MS_DEBUG_DEV(
						  "downgrading tmpSpatialLayer from %" PRIu16 " to %" PRIu16 " (packet:%" PRIu8
						  ":%" PRIu8 ") after keyframe (K-SVC)",
						  context->GetCurrentSpatialLayer(),
						  context->GetTargetSpatialLayer(),
						  packetSpatialLayer,
						  packetTemporalLayer);

						tmpSpatialLayer  = context->GetTargetSpatialLayer();
						//tmpTemporalLayer = 0; // Just in case.
					}
				}
				// In full SVC we do not need a keyframe.
				else
				{
					// clang-format off
					if (
						packetSpatialLayer == context->GetTargetSpatialLayer() &&
						!this->payloadDescriptor->y
					)
					// clang-format on
					{
						MS_DEBUG_DEV(
						  "downgrading tmpSpatialLayer from %" PRIu16 " to %" PRIu16 " (packet:%" PRIu8
						  ":%" PRIu8 ") without keyframe (full SVC)",
						  context->GetCurrentSpatialLayer(),
						  context->GetTargetSpatialLayer(),
						  packetSpatialLayer,
						  packetTemporalLayer);

						tmpSpatialLayer  = context->GetTargetSpatialLayer();
						//tmpTemporalLayer = 0; // Just in case.
					}
				}
			}

			// Filter spatial layers higher than current one (unless old packet).
			/* if (packetSpatialLayer > tmpSpatialLayer && !isOldPacket)
			{
				MS_DUMP(
					"filter spatial layer current: %u target: %u packet: S%u T%u ",
					context->GetCurrentSpatialLayer(),
					context->GetTargetSpatialLayer(),
					packetSpatialLayer,
					packetTemporalLayer);
				return false;
			} */

			// Check and handle temporal layer (unless old packet).
			if (!isOldPacket)
			{
				// Upgrade current temporal layer if needed.
				if (context->GetTargetTemporalLayer() > context->GetCurrentTemporalLayer())
				{
					// clang-format off
					if (
						packetTemporalLayer >= context->GetCurrentTemporalLayer() + 1 &&
						(
							context->GetCurrentTemporalLayer() == -1 ||
							this->payloadDescriptor->switchingUpPoint
						) &&
						!this->payloadDescriptor->z
					)
					// clang-format on
					{
						MS_DEBUG_DEV(
						  "upgrading tmpTemporalLayer from %" PRIu16 " to %" PRIu8 " (packet:%" PRIu8 ":%" PRIu8
						  ")",
						  context->GetCurrentTemporalLayer(),
						  packetTemporalLayer,
						  packetSpatialLayer,
						  packetTemporalLayer);

						tmpTemporalLayer = packetTemporalLayer;
					}
				}
				// Downgrade current temporal layer if needed.
				else if (context->GetTargetTemporalLayer() < context->GetCurrentTemporalLayer())
				{
					// clang-format off
					if (
						packetTemporalLayer == context->GetTargetTemporalLayer() &&
						!this->payloadDescriptor->y
					)
					// clang-format on
					{
						MS_DEBUG_DEV(
						  "downgrading tmpTemporalLayer from %" PRIu16 " to %" PRIu16 " (packet:%" PRIu8
						  ":%" PRIu8 ")",
						  context->GetCurrentTemporalLayer(),
						  context->GetTargetTemporalLayer(),
						  packetSpatialLayer,
						  packetTemporalLayer);

						tmpTemporalLayer = context->GetTargetTemporalLayer();
					}
				}

				// Filter temporal layers higher than current one.
				/* if (packetTemporalLayer > tmpTemporalLayer)
				{
					MS_DUMP(
						"filter temporal layer current: %u target: %u packet: S%u T%u ",
						context->GetCurrentSpatialLayer(),
						context->GetTargetSpatialLayer(),
						packetSpatialLayer,
						packetTemporalLayer);
				
					return false;
				} */
			}

			/* if (packetSpatialLayer == 0 && packetTemporalLayer == 1)
			{
				MS_DUMP(
					"filter packet: S%u T%u ",
					packetSpatialLayer,
					packetTemporalLayer);
			
				return false;
			} */

			// Set marker bit if needed.
			if (packetSpatialLayer == tmpSpatialLayer && !this->payloadDescriptor->y)
				marker = true;

			// Update the pictureId manager.
			if (this->payloadDescriptor->hasPictureId)
			{
				uint16_t pictureId;

				context->pictureIdManager.Input(this->payloadDescriptor->pictureId, pictureId);
			}

			// Update current spatial layer if needed.
			if (tmpSpatialLayer != context->GetCurrentSpatialLayer())
				context->SetCurrentSpatialLayer(tmpSpatialLayer);

			// Update current temporal layer if needed.
			if (tmpTemporalLayer != context->GetCurrentTemporalLayer())
				context->SetCurrentTemporalLayer(tmpTemporalLayer);

			return true;
		}

		void AV1X::PayloadDescriptorHandler::Restore(uint8_t* /*data*/)
		{
			MS_TRACE();
		}
	} // namespace Codecs
} // namespace RTC