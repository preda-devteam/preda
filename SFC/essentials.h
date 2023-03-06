#pragma once
/**
 * @file essentials.h
 * @author SFC dev team
 * @brief
 * @version 1.0
 * @date 2021-04-30
 * 
 * @copyright  
 * System Foundation Classes(SFC)
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *      * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *      * Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials provided
 *        with the distribution.
 *      * Neither the name of SFC.  nor the names of its
 *        contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *  
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.   
 */
/** \defgroup SFC SFC 
 *  @{
 */

#include "./core/rt/string_type.h"
#include "./core/rt/string_type_ops.h"
#include "./core/rt/buffer_type.h"
#include "./core/rt/json.h"

#include "./core/os/file_dir.h"
#include "./core/os/multi_thread.h"
#include "./core/inet/inet.h"

/*** Compiler/Linker Options on Linux ***/
// In [ Global Settings ]
// C++ Compiler Options: -std=c++14;-pthread;-mlzcnt;  (change -Wall to -w)
// Linker Options: -pthread;-ldl;-lX11;-mlzcnt;
// IPP Library: libippj_l.a;libippac_l.a;libippcp_l.a;libippi_l.a;libippsc_l.a;libippcc_l.a;libippcv_l.a;libipps_l.a;libippch_l.a;libippdc_l.a;libippm_l.a;libippvc_l.a;libippcore_l.a;libippdi_l.a;libippr_l.a;libippvm_l.a

/*** Compiler/Linker Options on Mac ***/
// Add file /src/os/objc_wrap.mm to the project
// General Tab -> Linked Frameworks and Libraries
// IOKit.framework, AppKit.framework
// IPP Library: all files in /libs/mac/*.a

/** @}*/