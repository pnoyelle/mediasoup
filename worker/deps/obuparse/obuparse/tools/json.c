/*
 * Copyright (c) 2020, Derek Buitenhuis
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * This file was mostly autogenerated by 'genstruct', then cleaned up manually after.
 */

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#include "../obuparse.h"

void print_json_film_grain_params(OBPFilmGrainParameters *my_struct)
{
    printf("        \"apply_grain\": %d,\n", my_struct->apply_grain);
    printf("        \"grain_seed\": %"PRIu16",\n", my_struct->grain_seed);
    printf("        \"update_grain\": %d,\n", my_struct->update_grain);
    printf("        \"film_grain_params_ref_idx\": %"PRIu8",\n", my_struct->film_grain_params_ref_idx);
    printf("        \"num_y_points\": %"PRIu8",\n", my_struct->num_y_points);
    printf("        \"point_y_value\": [\n");
    for (int i = 0; i < 16; i++) {
        printf("        %"PRIu8"", my_struct->point_y_value[i]);
        printf("%s", i == 16 - 1 ? "\n" : ",\n");
    }
    printf("        ],\n");
    printf("        \"point_y_scaling\": [\n");
    for (int i = 0; i < 16; i++) {
        printf("        %"PRIu8"", my_struct->point_y_scaling[i]);
        printf("%s", i == 16 - 1 ? "\n" : ",\n");
    }
    printf("        ],\n");
    printf("        \"chroma_scaling_from_luma\": %d,\n", my_struct->chroma_scaling_from_luma);
    printf("        \"num_cb_points\": %"PRIu8",\n", my_struct->num_cb_points);
    printf("        \"point_cb_value\": [\n");
    for (int i = 0; i < 16; i++) {
        printf("        %"PRIu8"", my_struct->point_cb_value[i]);
        printf("%s", i == 16 - 1 ? "\n" : ",\n");
    }
    printf("        ],\n");
    printf("        \"point_cb_scaling\": [\n");
    for (int i = 0; i < 16; i++) {
        printf("        %"PRIu8"", my_struct->point_cb_scaling[i]);
        printf("%s", i == 16 - 1 ? "\n" : ",\n");
    }
    printf("        ],\n");
    printf("        \"num_cr_points\": %"PRIu8",\n", my_struct->num_cr_points);
    printf("        \"point_cr_value\": [\n");
    for (int i = 0; i < 16; i++) {
        printf("        %"PRIu8"", my_struct->point_cr_value[i]);
        printf("%s", i == 16 - 1 ? "\n" : ",\n");
    }
    printf("        ],\n");
    printf("        \"point_cr_scaling\": [\n");
    for (int i = 0; i < 16; i++) {
        printf("        %"PRIu8"", my_struct->point_cr_scaling[i]);
        printf("%s", i == 16 - 1 ? "\n" : ",\n");
    }
    printf("        ],\n");
    printf("        \"grain_scaling_minus_8\": %"PRIu8",\n", my_struct->grain_scaling_minus_8);
    printf("        \"ar_coeff_lag\": %"PRIu8",\n", my_struct->ar_coeff_lag);
    printf("        \"ar_coeffs_y_plus_128\": [\n");
    for (int i = 0; i < 24; i++) {
        printf("        %"PRIu8"", my_struct->ar_coeffs_y_plus_128[i]);
        printf("%s", i == 24 - 1 ? "\n" : ",\n");
    }
    printf("        ],\n");
    printf("        \"ar_coeffs_cb_plus_128\": [\n");
    for (int i = 0; i < 25; i++) {
        printf("        %"PRIu8"", my_struct->ar_coeffs_cb_plus_128[i]);
        printf("%s", i == 25 - 1 ? "\n" : ",\n");
    }
    printf("        ],\n");
    printf("        \"ar_coeffs_cr_plus_128\": [\n");
    for (int i = 0; i < 25; i++) {
        printf("        %"PRIu8"", my_struct->ar_coeffs_cr_plus_128[i]);
        printf("%s", i == 25 - 1 ? "\n" : ",\n");
    }
    printf("        ],\n");
    printf("        \"ar_coeff_shift_minus_6\": %"PRIu8",\n", my_struct->ar_coeff_shift_minus_6);
    printf("        \"grain_scale_shift\": %"PRIu8",\n", my_struct->grain_scale_shift);
    printf("        \"cb_mult\": %"PRIu8",\n", my_struct->cb_mult);
    printf("        \"cb_luma_mult\": %"PRIu8",\n", my_struct->cb_luma_mult);
    printf("        \"cb_offset\": %"PRIu16",\n", my_struct->cb_offset);
    printf("        \"cr_mult\": %"PRIu8",\n", my_struct->cr_mult);
    printf("        \"cr_luma_mult\": %"PRIu8",\n", my_struct->cr_luma_mult);
    printf("        \"cr_offset\": %"PRIu16",\n", my_struct->cr_offset);
    printf("        \"overlap_flag\": %d,\n", my_struct->overlap_flag);
    printf("        \"clip_to_restricted_range\": %d\n", my_struct->clip_to_restricted_range);
}

void print_json_frame_header(OBPFrameHeader *my_struct)
{
    printf("{\n");
    printf("    \"show_existing_frame\": %d,\n", my_struct->show_existing_frame);
    printf("    \"frame_to_show_map_idx\": %"PRIu8",\n", my_struct->frame_to_show_map_idx);
    printf("    \"temporal_point_info\": {\n");
    printf("        \"frame_presentation_time\": %"PRIu32"\n", my_struct->temporal_point_info.frame_presentation_time);
    printf("    },\n");
    printf("    \"display_frame_id\": %"PRIu32",\n", my_struct->display_frame_id);
    printf("    \"frame_type\": %d,\n", my_struct->frame_type);
    printf("    \"show_frame\": %d,\n", my_struct->show_frame);
    printf("    \"showable_frame\": %d,\n", my_struct->showable_frame);
    printf("    \"error_resilient_mode\": %d,\n", my_struct->error_resilient_mode);
    printf("    \"disable_cdf_update\": %d,\n", my_struct->disable_cdf_update);
    printf("    \"allow_screen_content_tools\": %d,\n", my_struct->allow_screen_content_tools);
    printf("    \"force_integer_mv\": %d,\n", my_struct->force_integer_mv);
    printf("    \"current_frame_id\": %"PRIu32",\n", my_struct->current_frame_id);
    printf("    \"frame_size_override_flag\": %d,\n", my_struct->frame_size_override_flag);
    printf("    \"order_hint\": %"PRIu8",\n", my_struct->order_hint);
    printf("    \"primary_ref_frame\": %"PRIu8",\n", my_struct->primary_ref_frame);
    printf("    \"buffer_removal_time_present_flag\": %d,\n", my_struct->buffer_removal_time_present_flag);
    printf("    \"buffer_removal_time\": [\n");
    for (int i = 0; i < 32; i++) {
        printf("    %"PRIu32"", my_struct->buffer_removal_time[i]);
        printf("%s", i == 32 - 1 ? "\n" : ",\n");
    }
    printf("    ],\n");
    printf("    \"refresh_frame_flags\": %"PRIu8",\n", my_struct->refresh_frame_flags);
    printf("    \"ref_order_hint\": [\n");
    for (int i = 0; i < 8; i++) {
        printf("    %"PRIu8"", my_struct->ref_order_hint[i]);
        printf("%s", i == 8 - 1 ? "\n" : ",\n");
    }
    printf("    ],\n");
    printf("    \"frame_width_minus_1\": %"PRIu32",\n", my_struct->frame_width_minus_1);
    printf("    \"frame_height_minus_1\": %"PRIu32",\n", my_struct->frame_height_minus_1);
    printf("    \"superres_params\": {\n");
    printf("        \"use_superres\": %d,\n", my_struct->superres_params.use_superres);
    printf("        \"coded_denom\": %"PRIu8"\n", my_struct->superres_params.coded_denom);
    printf("    },\n");
    printf("    \"render_and_frame_size_different\": %d,\n", my_struct->render_and_frame_size_different);
    printf("    \"render_width_minus_1\": %"PRIu16",\n", my_struct->render_width_minus_1);
    printf("    \"render_height_minus_1\": %"PRIu16",\n", my_struct->render_height_minus_1);
    printf("    \"RenderWidth\": %"PRIu32",\n", my_struct->RenderWidth);
    printf("    \"RenderHeight\": %"PRIu32",\n", my_struct->RenderHeight);
    printf("    \"allow_intrabc\": %d,\n", my_struct->allow_intrabc);
    printf("    \"frame_refs_short_signaling\": %d,\n", my_struct->frame_refs_short_signaling);
    printf("    \"last_frame_idx\": %"PRIu8",\n", my_struct->last_frame_idx);
    printf("    \"gold_frame_idx\": %"PRIu8",\n", my_struct->gold_frame_idx);
    printf("    \"ref_frame_idx\": [\n");
    for (int i = 0; i < 7; i++) {
        printf("    %"PRIu8"", my_struct->ref_frame_idx[i]);
        printf("%s", i == 7 - 1 ? "\n" : ",\n");
    }
    printf("    ],\n");
    printf("    \"delta_frame_id_minus_1\": [\n");
    for (int i = 0; i < 7; i++) {
        printf("    %"PRIu8"", my_struct->delta_frame_id_minus_1[i]);
        printf("%s", i == 7 - 1 ? "\n" : ",\n");
    }
    printf("    ],\n");
    printf("    \"found_ref\": %d,\n", my_struct->found_ref);
    printf("    \"allow_high_precision_mv\": %d,\n", my_struct->allow_high_precision_mv);
    printf("    \"interpolation_filter\": {\n");
    printf("        \"is_filter_switchable\": %d,\n", my_struct->interpolation_filter.is_filter_switchable);
    printf("        \"interpolation_filter\": %"PRIu8"\n", my_struct->interpolation_filter.interpolation_filter);
    printf("    },\n");
    printf("    \"is_motion_mode_switchable\": %d,\n", my_struct->is_motion_mode_switchable);
    printf("    \"use_ref_frame_mvs\": %d,\n", my_struct->use_ref_frame_mvs);
    printf("    \"disable_frame_end_update_cdf\": %d,\n", my_struct->disable_frame_end_update_cdf);
    printf("    \"tile_info\": {\n");
    printf("        \"uniform_tile_spacing_flag\": %d,\n", my_struct->tile_info.uniform_tile_spacing_flag);
    printf("        \"TileRows\": %"PRIu16",\n", my_struct->tile_info.TileRows);
    printf("        \"TileCols\": %"PRIu16",\n", my_struct->tile_info.TileCols);
    printf("        \"context_update_tile_id\": %"PRIu32",\n", my_struct->tile_info.context_update_tile_id);
    printf("        \"tile_size_bytes_minus_1\": %"PRIu8"\n", my_struct->tile_info.tile_size_bytes_minus_1);
    printf("    },\n");
    printf("    \"quantization_params\": {\n");
    printf("        \"base_q_idx\": %"PRIu8",\n", my_struct->quantization_params.base_q_idx);
    printf("        \"diff_uv_delta\": %d,\n", my_struct->quantization_params.diff_uv_delta);
    printf("        \"using_qmatrix\": %d,\n", my_struct->quantization_params.using_qmatrix);
    printf("        \"qm_y\": %"PRIu8",\n", my_struct->quantization_params.qm_y);
    printf("        \"qm_u\": %"PRIu8",\n", my_struct->quantization_params.qm_u);
    printf("        \"qm_v\": %"PRIu8"\n", my_struct->quantization_params.qm_v);
    printf("    },\n");
    printf("    \"segmentation_params\": {\n");
    printf("        \"segmentation_enabled\": %d,\n", my_struct->segmentation_params.segmentation_enabled);
    printf("        \"segmentation_update_map\": %d,\n", my_struct->segmentation_params.segmentation_update_map);
    printf("        \"segmentation_temporal_update\": %d,\n", my_struct->segmentation_params.segmentation_temporal_update);
    printf("        \"segmentation_update_data\": %d\n", my_struct->segmentation_params.segmentation_update_data);
    printf("    },\n");
    printf("    \"delta_q_params\": {\n");
    printf("        \"delta_q_present\": %d,\n", my_struct->delta_q_params.delta_q_present);
    printf("        \"delta_q_res\": %"PRIu8"\n", my_struct->delta_q_params.delta_q_res);
    printf("    },\n");
    printf("    \"delta_lf_params\": {\n");
    printf("        \"delta_lf_present\": %d,\n", my_struct->delta_lf_params.delta_lf_present);
    printf("        \"delta_lf_res\": %"PRIu8",\n", my_struct->delta_lf_params.delta_lf_res);
    printf("        \"delta_lf_multi\": %d\n", my_struct->delta_lf_params.delta_lf_multi);
    printf("    },\n");
    printf("    \"loop_filter_params\": {\n");
    printf("        \"loop_filter_level\": [\n");
    for (int i = 0; i < 4; i++) {
        printf("        %"PRIu8"", my_struct->loop_filter_params.loop_filter_level[i]);
        printf("%s", i == 4 - 1 ? "\n" : ",\n");
    }
    printf("        ],\n");
    printf("        \"loop_filter_sharpness\": %"PRIu8",\n", my_struct->loop_filter_params.loop_filter_sharpness);
    printf("        \"loop_filter_delta_enabled\": %d,\n", my_struct->loop_filter_params.loop_filter_delta_enabled);
    printf("        \"loop_filter_delta_update\": %d,\n", my_struct->loop_filter_params.loop_filter_delta_update);
    printf("        \"update_ref_delta\": [\n");
    for (int i = 0; i < 8; i++) {
        printf("        %d", my_struct->loop_filter_params.update_ref_delta[i]);
        printf("%s", i == 8 - 1 ? "\n" : ",\n");
    }
    printf("        ],\n");
    printf("        \"loop_filter_ref_deltas\": [\n");
    for (int i = 0; i < 8; i++) {
        printf("        %"PRId8"", my_struct->loop_filter_params.loop_filter_ref_deltas[i]);
        printf("%s", i == 8 - 1 ? "\n" : ",\n");
    }
    printf("        ],\n");
    printf("        \"update_mode_delta\": [\n");
    for (int i = 0; i < 8; i++) {
        printf("        %d", my_struct->loop_filter_params.update_mode_delta[i]);
        printf("%s", i == 8 - 1 ? "\n" : ",\n");
    }
    printf("        ],\n");
    printf("        \"loop_filter_mode_deltas\": [\n");
    for (int i = 0; i < 8; i++) {
        printf("        %"PRId8"", my_struct->loop_filter_params.loop_filter_mode_deltas[i]);
        printf("%s", i == 8 - 1 ? "\n" : ",\n");
    }
    printf("        ]\n");
    printf("    },\n");
    printf("    \"cdef_params\": {\n");
    printf("        \"cdef_damping_minus_3\": %"PRIu8",\n", my_struct->cdef_params.cdef_damping_minus_3);
    printf("        \"cdef_bits\": %"PRIu8",\n", my_struct->cdef_params.cdef_bits);
    printf("        \"cdef_y_pri_strength\": [\n");
    for (int i = 0; i < 8; i++) {
        printf("        %"PRIu8"", my_struct->cdef_params.cdef_y_pri_strength[i]);
        printf("%s", i == 8 - 1 ? "\n" : ",\n");
    }
    printf("        ],\n");
    printf("        \"cdef_y_sec_strength\": [\n");
    for (int i = 0; i < 8; i++) {
        printf("        %"PRIu8"", my_struct->cdef_params.cdef_y_sec_strength[i]);
        printf("%s", i == 8 - 1 ? "\n" : ",\n");
    }
    printf("        ],\n");
    printf("        \"cdef_uv_pri_strength\": [\n");
    for (int i = 0; i < 8; i++) {
        printf("        %"PRIu8"", my_struct->cdef_params.cdef_uv_pri_strength[i]);
        printf("%s", i == 8 - 1 ? "\n" : ",\n");
    }
    printf("        ],\n");
    printf("        \"cdef_uv_sec_strength\": [\n");
    for (int i = 0; i < 8; i++) {
        printf("        %"PRIu8"", my_struct->cdef_params.cdef_uv_sec_strength[i]);
        printf("%s", i == 8 - 1 ? "\n" : ",\n");
    }
    printf("        ]\n");
    printf("    },\n");
    printf("    \"lr_params\": {\n");
    printf("        \"lr_type\": [\n");
    for (int i = 0; i < 3; i++) {
        printf("        %"PRIu8"", my_struct->lr_params.lr_type[i]);
        printf("%s", i == 3 - 1 ? "\n" : ",\n");
    }
    printf("        ],\n");
    printf("        \"lr_unit_shift\": %"PRIu8",\n", my_struct->lr_params.lr_unit_shift);
    printf("        \"lr_uv_shift\": %d\n", my_struct->lr_params.lr_uv_shift);
    printf("    },\n");
    printf("    \"tx_mode_select\": %d,\n", my_struct->tx_mode_select);
    printf("    \"skip_mode_present\": %d,\n", my_struct->skip_mode_present);
    printf("    \"reference_select\": %d,\n", my_struct->reference_select);
    printf("    \"allow_warped_motion\": %d,\n", my_struct->allow_warped_motion);
    printf("    \"reduced_tx_set\": %d,\n", my_struct->reduced_tx_set);
    printf("    \"global_motion_params\": {\n");
    printf("        \"gm_type\": [\n");
    for (int i = 0; i < 8; i++) {
        printf("        %"PRIu8"", my_struct->global_motion_params.gm_type[i]);
        printf("%s", i == 8 - 1 ? "\n" : ",\n");
    }
    printf("        ],\n");
    printf("        \"gm_params\": [\n");
    for (int i = 0; i < 8; i++) {
        printf("            [\n");
        for (int j = 0; j < 6; j++) {
            printf("            %"PRId32"", my_struct->global_motion_params.gm_params[i][j]);
            printf("%s", j == 6 - 1 ? "\n" : ",\n");
        }
        printf("            ]");
        printf("%s", i == 8 - 1 ? "\n" : ",\n");
    }
    printf("        ],\n");
    printf("        \"prev_gm_params\": [\n");
    for (int i = 0; i < 8; i++) {
        printf("            [\n");
        for (int j = 0; j < 6; j++) {
            printf("        %"PRIu32"", my_struct->global_motion_params.prev_gm_params[i][j]);
            printf("%s", j == 6 - 1 ? "\n" : ",\n");
        }
        printf("            ]");
        printf("%s", i == 8 - 1 ? "\n" : ",\n");
    }
    printf("        ]\n");
    printf("    },\n");
    printf("    \"film_grain_params\": {\n");
    print_json_film_grain_params(&my_struct->film_grain_params);
    printf("    }\n");
    printf("}\n");
}

void print_json_sequence_header(OBPSequenceHeader *my_struct)
{
    printf("{\n");
    printf("    \"seq_profile\": %"PRIu8",\n", my_struct->seq_profile);
    printf("    \"still_picture\": %d,\n", my_struct->still_picture);
    printf("    \"reduced_still_picture_header\": %d,\n", my_struct->reduced_still_picture_header);
    printf("    \"timing_info_present_flag\": %d,\n", my_struct->timing_info_present_flag);
    printf("    \"timing_info\": {\n");
    printf("        \"num_units_in_display_tick\": %"PRIu32",\n", my_struct->timing_info.num_units_in_display_tick);
    printf("        \"time_scale\": %"PRIu32",\n", my_struct->timing_info.time_scale);
    printf("        \"equal_picture_interval\": %d,\n", my_struct->timing_info.equal_picture_interval);
    printf("        \"num_ticks_per_picture_minus_1\": %"PRIu32"\n", my_struct->timing_info.num_ticks_per_picture_minus_1);
    printf("    },\n");
    printf("    \"decoder_model_info_present_flag\": %d,\n", my_struct->decoder_model_info_present_flag);
    printf("    \"decoder_model_info\": {\n");
    printf("        \"buffer_delay_length_minus_1\": %"PRIu8",\n", my_struct->decoder_model_info.buffer_delay_length_minus_1);
    printf("        \"num_units_in_decoding_tick\": %"PRIu32",\n", my_struct->decoder_model_info.num_units_in_decoding_tick);
    printf("        \"buffer_removal_time_length_minus_1\": %"PRIu8",\n", my_struct->decoder_model_info.buffer_removal_time_length_minus_1);
    printf("        \"frame_presentation_time_length_minus_1\": %"PRIu8"\n", my_struct->decoder_model_info.frame_presentation_time_length_minus_1);
    printf("    },\n");
    printf("    \"initial_display_delay_present_flag\": %d,\n", my_struct->initial_display_delay_present_flag);
    printf("    \"operating_points_cnt_minus_1\": %"PRIu8",\n", my_struct->operating_points_cnt_minus_1);
    printf("    \"operating_point_idc\": [\n");
    for (int i = 0; i < 32; i++) {
        printf("    %"PRIu8"", my_struct->operating_point_idc[i]);
        printf("%s", i == 32 - 1 ? "\n" : ",\n");
    }
    printf("    ],\n");
    printf("    \"seq_level_idx\": [\n");
    for (int i = 0; i < 32; i++) {
        printf("    %"PRIu8"", my_struct->seq_level_idx[i]);
        printf("%s", i == 32 - 1 ? "\n" : ",\n");
    }
    printf("    ],\n");
    printf("    \"seq_tier\": [\n");
    for (int i = 0; i < 32; i++) {
        printf("    %"PRIu8"", my_struct->seq_tier[i]);
        printf("%s", i == 32 - 1 ? "\n" : ",\n");
    }
    printf("    ],\n");
    printf("    \"decoder_model_present_for_this_op\": [\n");
    for (int i = 0; i < 32; i++) {
        printf("    %d", my_struct->decoder_model_present_for_this_op[i]);
        printf("%s", i == 32 - 1 ? "\n" : ",\n");
    }
    printf("    ],\n");
    printf("    \"operating_parameters_info\": [\n");
    for (int i = 0; i < 32; i++) {
        printf("    {\n");
        printf("        \"decoder_buffer_delay\": %"PRIu64",\n", my_struct->operating_parameters_info[i].decoder_buffer_delay);
        printf("        \"encoder_buffer_delay\": %"PRIu64",\n", my_struct->operating_parameters_info[i].encoder_buffer_delay);
        printf("        \"low_delay_mode_flag\": %d\n", my_struct->operating_parameters_info[i].low_delay_mode_flag);
        printf("    }");
        printf("%s", i == 32 - 1 ? "\n" : ",\n");
    }
    printf("    ],\n");
    printf("    \"initial_display_delay_present_for_this_op\": [\n");
    for (int i = 0; i < 32; i++) {
        printf("    %d", my_struct->initial_display_delay_present_for_this_op[i]);
        printf("%s", i == 32 - 1 ? "\n" : ",\n");
    }
    printf("    ],\n");
    printf("    \"initial_display_delay_minus_1\": [\n");
    for (int i = 0; i < 32; i++) {
        printf("    %"PRIu8"", my_struct->initial_display_delay_minus_1[i]);
        printf("%s", i == 32 - 1 ? "\n" : ",\n");
    }
    printf("    ],\n");
    printf("    \"frame_width_bits_minus_1\": %"PRIu8",\n", my_struct->frame_width_bits_minus_1);
    printf("    \"frame_height_bits_minus_1\": %"PRIu8",\n", my_struct->frame_height_bits_minus_1);
    printf("    \"max_frame_width_minus_1\": %"PRIu32",\n", my_struct->max_frame_width_minus_1);
    printf("    \"max_frame_height_minus_1\": %"PRIu32",\n", my_struct->max_frame_height_minus_1);
    printf("    \"frame_id_numbers_present_flag\": %d,\n", my_struct->frame_id_numbers_present_flag);
    printf("    \"delta_frame_id_length_minus_2\": %"PRIu8",\n", my_struct->delta_frame_id_length_minus_2);
    printf("    \"additional_frame_id_length_minus_1\": %"PRIu8",\n", my_struct->additional_frame_id_length_minus_1);
    printf("    \"use_128x128_superblock\": %d,\n", my_struct->use_128x128_superblock);
    printf("    \"enable_filter_intra\": %d,\n", my_struct->enable_filter_intra);
    printf("    \"enable_intra_edge_filter\": %d,\n", my_struct->enable_intra_edge_filter);
    printf("    \"enable_interintra_compound\": %d,\n", my_struct->enable_interintra_compound);
    printf("    \"enable_masked_compound\": %d,\n", my_struct->enable_masked_compound);
    printf("    \"enable_warped_motion\": %d,\n", my_struct->enable_warped_motion);
    printf("    \"enable_dual_filter\": %d,\n", my_struct->enable_dual_filter);
    printf("    \"enable_order_hint\": %d,\n", my_struct->enable_order_hint);
    printf("    \"enable_jnt_comp\": %d,\n", my_struct->enable_jnt_comp);
    printf("    \"enable_ref_frame_mvs\": %d,\n", my_struct->enable_ref_frame_mvs);
    printf("    \"seq_choose_screen_content_tools\": %d,\n", my_struct->seq_choose_screen_content_tools);
    printf("    \"seq_force_screen_content_tools\": %d,\n", my_struct->seq_force_screen_content_tools);
    printf("    \"seq_choose_integer_mv\": %d,\n", my_struct->seq_choose_integer_mv);
    printf("    \"seq_force_integer_mv\": %d,\n", my_struct->seq_force_integer_mv);
    printf("    \"order_hint_bits_minus_1\": %"PRIu8",\n", my_struct->order_hint_bits_minus_1);
    printf("    \"OrderHintBits\": %"PRIu8",\n", my_struct->OrderHintBits);
    printf("    \"enable_superres\": %d,\n", my_struct->enable_superres);
    printf("    \"enable_cdef\": %d,\n", my_struct->enable_cdef);
    printf("    \"enable_restoration\": %d,\n", my_struct->enable_restoration);
    printf("    \"color_config\": {\n");
    printf("        \"high_bitdepth\": %d,\n", my_struct->color_config.high_bitdepth);
    printf("        \"twelve_bit\": %d,\n", my_struct->color_config.twelve_bit);
    printf("        \"BitDepth\": %"PRIu8",\n", my_struct->color_config.BitDepth);
    printf("        \"mono_chrome\": %d,\n", my_struct->color_config.mono_chrome);
    printf("        \"NumPlanes\": %"PRIu8",\n", my_struct->color_config.NumPlanes);
    printf("        \"color_description_present_flag\": %d,\n", my_struct->color_config.color_description_present_flag);
    printf("        \"color_primaries\": %d,\n", my_struct->color_config.color_primaries);
    printf("        \"transfer_characteristics\": %d,\n", my_struct->color_config.transfer_characteristics);
    printf("        \"matrix_coefficients\": %d,\n", my_struct->color_config.matrix_coefficients);
    printf("        \"color_range\": %d,\n", my_struct->color_config.color_range);
    printf("        \"subsampling_x\": %d,\n", my_struct->color_config.subsampling_x);
    printf("        \"subsampling_y\": %d,\n", my_struct->color_config.subsampling_y);
    printf("        \"chroma_sample_position\": %d,\n", my_struct->color_config.chroma_sample_position);
    printf("        \"separate_uv_delta_q\": %d\n", my_struct->color_config.separate_uv_delta_q);
    printf("    },\n");
    printf("    \"film_grain_params_present\": %d\n", my_struct->film_grain_params_present);
    printf("}\n");
}

void print_json_metadata(OBPMetadata *my_struct)
{
    printf("{\n");
    printf("    \"metadata_type\": %d,\n", my_struct->metadata_type);
    printf("    \"metadata_itut_t35\": {\n");
    printf("        \"itu_t_t35_country_code\": %"PRIu8",\n", my_struct->metadata_itut_t35.itu_t_t35_country_code);
    printf("        \"itu_t_t35_country_code_extension_byte\": %"PRIu8",\n", my_struct->metadata_itut_t35.itu_t_t35_country_code_extension_byte);
    /* itu_t_t35_payload_bytes not printed. */
    printf("        \"itu_t_t35_payload_bytes_size\": %zu\n", my_struct->metadata_itut_t35.itu_t_t35_payload_bytes_size);
    printf("    },\n");
    printf("    \"metadata_hdr_cll\": {\n");
    printf("        \"max_cll\": %"PRIu16",\n", my_struct->metadata_hdr_cll.max_cll);
    printf("        \"max_fall\": %"PRIu16"\n", my_struct->metadata_hdr_cll.max_fall);
    printf("    },\n");
    printf("    \"metadata_hdr_mdcv\": {\n");
    printf("        \"primary_chromaticity_x\": [\n");
    for (int i = 0; i < 3; i++) {
        printf("        %"PRIu16"", my_struct->metadata_hdr_mdcv.primary_chromaticity_x[i]);
        printf("%s", i == 3 - 1 ? "\n" : ",\n");
    }
    printf("        ],\n");
    printf("        \"primary_chromaticity_y\": [\n");
    for (int i = 0; i < 3; i++) {
        printf("        %"PRIu16"", my_struct->metadata_hdr_mdcv.primary_chromaticity_y[i]);
        printf("%s", i == 3 - 1 ? "\n" : ",\n");
    }
    printf("        ],\n");
    printf("        \"white_point_chromaticity_x\": %"PRIu16",\n", my_struct->metadata_hdr_mdcv.white_point_chromaticity_x);
    printf("        \"white_point_chromaticity_y\": %"PRIu16",\n", my_struct->metadata_hdr_mdcv.white_point_chromaticity_y);
    printf("        \"luminance_max\": %"PRIu32",\n", my_struct->metadata_hdr_mdcv.luminance_max);
    printf("        \"luminance_min\": %"PRIu32"\n", my_struct->metadata_hdr_mdcv.luminance_min);
    printf("    },\n");
    printf("    \"metadata_scalability\": {\n");
    printf("        \"scalability_mode_idc\": %"PRIu8",\n", my_struct->metadata_scalability.scalability_mode_idc);
    printf("        \"scalability_structure\": {\n");
    printf("            \"spatial_layers_cnt_minus_1\": %"PRIu8",\n", my_struct->metadata_scalability.scalability_structure.spatial_layers_cnt_minus_1);
    printf("            \"spatial_layer_dimensions_present_flag\": %d,\n", my_struct->metadata_scalability.scalability_structure.spatial_layer_dimensions_present_flag);
    printf("            \"spatial_layer_description_present_flag\": %d,\n", my_struct->metadata_scalability.scalability_structure.spatial_layer_description_present_flag);
    printf("            \"temporal_group_description_present_flag\": %d,\n", my_struct->metadata_scalability.scalability_structure.temporal_group_description_present_flag);
    printf("            \"scalability_structure_reserved_3bits\": %"PRIu8",\n", my_struct->metadata_scalability.scalability_structure.scalability_structure_reserved_3bits);
    printf("            \"spatial_layer_max_width\": [\n");
    for (int i = 0; i < 3; i++) {
        printf("            %"PRIu16"", my_struct->metadata_scalability.scalability_structure.spatial_layer_max_width[i]);
        printf("%s", i == 3 - 1 ? "\n" : ",\n");
    }
    printf("            ],\n");
    printf("            \"spatial_layer_max_height\": [\n");
    for (int i = 0; i < 3; i++) {
        printf("            %"PRIu16"", my_struct->metadata_scalability.scalability_structure.spatial_layer_max_height[i]);
        printf("%s", i == 3 - 1 ? "\n" : ",\n");
    }
    printf("            ],\n");
    printf("            \"spatial_layer_ref_id\": [\n");
    for (int i = 0; i < 3; i++) {
        printf("            %"PRIu8"", my_struct->metadata_scalability.scalability_structure.spatial_layer_ref_id[i]);
        printf("%s", i == 3 - 1 ? "\n" : ",\n");
    }
    printf("            ],\n");
    printf("            \"temporal_group_size\": %"PRIu8",\n", my_struct->metadata_scalability.scalability_structure.temporal_group_size);
    printf("            \"temporal_group_temporal_id\": [\n");
    for (int i = 0; i < 256; i++) {
        printf("            %"PRIu8"", my_struct->metadata_scalability.scalability_structure.temporal_group_temporal_id[i]);
        printf("%s", i == 256 - 1 ? "\n" : ",\n");
    }
    printf("            ],\n");
    printf("            \"temporal_group_temporal_switching_up_point_flag\": [\n");
    for (int i = 0; i < 256; i++) {
        printf("            %d", my_struct->metadata_scalability.scalability_structure.temporal_group_temporal_switching_up_point_flag[i]);
        printf("%s", i == 256 - 1 ? "\n" : ",\n");
    }
    printf("            ],\n");
    printf("            \"temporal_group_spatial_switching_up_point_flag\": [\n");
    for (int i = 0; i < 256; i++) {
        printf("            %d", my_struct->metadata_scalability.scalability_structure.temporal_group_spatial_switching_up_point_flag[i]);
        printf("%s", i == 256 - 1 ? "\n" : ",\n");
    }
    printf("            ],\n");
    printf("            \"temporal_group_ref_cnt\": [\n");
    for (int i = 0; i < 256; i++) {
        printf("            %"PRIu8"", my_struct->metadata_scalability.scalability_structure.temporal_group_ref_cnt[i]);
        printf("%s", i == 256 - 1 ? "\n" : ",\n");
    }
    printf("            ],\n");
    printf("            \"temporal_group_ref_pic_diff[256]\": [\n");
    for (int i = 0; i < 256; i++) {
        printf("                [\n");
        for (int j = 0; j < 8; j++) {
            printf("                %"PRIu8"", my_struct->metadata_scalability.scalability_structure.temporal_group_ref_pic_diff[i][j]);
            printf("%s", j == 8 - 1 ? "\n" : ",\n");
        }
        printf("                ]\n");
        printf("%s", i == 256 - 1 ? "\n" : ",\n");
    }
    printf("            ]\n");
    printf("        }\n");
    printf("    },\n");
    printf("    \"metadata_timecode\": {\n");
    printf("        \"counting_type\": %"PRIu8",\n", my_struct->metadata_timecode.counting_type);
    printf("        \"full_timestamp_flag\": %d,\n", my_struct->metadata_timecode.full_timestamp_flag);
    printf("        \"discontinuity_flag\": %d,\n", my_struct->metadata_timecode.discontinuity_flag);
    printf("        \"cnt_dropped_flag\": %d,\n", my_struct->metadata_timecode.cnt_dropped_flag);
    printf("        \"n_frames\": %"PRIu16",\n", my_struct->metadata_timecode.n_frames);
    printf("        \"seconds_value\": %"PRIu8",\n", my_struct->metadata_timecode.seconds_value);
    printf("        \"minutes_value\": %"PRIu8",\n", my_struct->metadata_timecode.minutes_value);
    printf("        \"hours_value\": %"PRIu8",\n", my_struct->metadata_timecode.hours_value);
    printf("        \"seconds_flag\": %d,\n", my_struct->metadata_timecode.seconds_flag);
    printf("        \"minutes_flag\": %d,\n", my_struct->metadata_timecode.minutes_flag);
    printf("        \"hours_flag\": %d,\n", my_struct->metadata_timecode.hours_flag);
    printf("        \"time_offset_length\": %"PRIu8",\n", my_struct->metadata_timecode.time_offset_length);
    printf("        \"time_offset_value\": %"PRIu32"\n", my_struct->metadata_timecode.time_offset_value);
    printf("    },\n");
    printf("    \"unregistered\": {\n");
    /* buf data not printed */
    printf("        \"buf_size\": %zu\n", my_struct->unregistered.buf_size);
    printf("    }\n");
    printf("}\n");
}

void print_json_tile_list(OBPTileList *my_struct)
{
    printf("{\n");
    printf("    \"output_frame_width_in_tiles_minus_1\": %"PRIu8",\n", my_struct->output_frame_width_in_tiles_minus_1);
    printf("    \"output_frame_height_in_tiles_minus_1\": %"PRIu8",\n", my_struct->output_frame_height_in_tiles_minus_1);
    printf("    \"tile_count_minus_1\": %"PRIu16",\n", my_struct->tile_count_minus_1);
    printf("    \"tile_list_entry\": [\n");
    for (uint16_t i = 0; i <= my_struct->tile_count_minus_1; i++) {
        printf("    {\n");
        printf("        \"anchor_frame_idx\": %"PRIu8",\n", my_struct->tile_list_entry[i].anchor_frame_idx);
        printf("        \"anchor_tile_row\": %"PRIu8",\n", my_struct->tile_list_entry[i].anchor_tile_row);
        printf("        \"anchor_tile_col\": %"PRIu8",\n", my_struct->tile_list_entry[i].anchor_tile_col);
        printf("        \"tile_data_size_minus_1\": %"PRIu16",\n", my_struct->tile_list_entry[i].tile_data_size_minus_1);
        /* coded_tile_data buffer not printed. */
        printf("        \"coded_tile_data_size\": %zu\n", my_struct->tile_list_entry[i].coded_tile_data_size);
        printf("    }");
        printf("%s", i == my_struct->tile_count_minus_1 ? "\n" : ",\n");
    }
    printf("    ]\n");
    printf("}\n");
}

void print_json_tile_group(OBPTileGroup *my_struct)
{
    printf("{\n");
    printf("    \"NumTiles\": %"PRIu16",\n", my_struct->NumTiles);
    printf("    \"tile_start_and_end_present_flag\": %d,\n", my_struct->tile_start_and_end_present_flag);
    printf("    \"tg_start\": %"PRIu16",\n", my_struct->tg_start);
    printf("    \"tg_end\": %"PRIu16",\n", my_struct->tg_end);
    printf("    \"TileSize\": [\n");
    for (uint32_t i = my_struct->tg_start; i <= my_struct->tg_end; i++) {
        printf("    %"PRIu64"", my_struct->TileSize[i]);
        printf("%s", i == my_struct->tg_end ? "\n" : ",\n");
    }
    printf("    ]\n");
    printf("}\n");
}

