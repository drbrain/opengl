/*
 * Copyright (C) 2006 Peter McLain <peter.mclain@gmail.com>
 *
 * This program is distributed under the terms of the MIT license.
 * See the included MIT-LICENSE file for the terms of this license.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

%module GL
#ifdef SWIGMAC
%header %{
#include "/System/Library/Frameworks/OpenGL.framework/Headers/gl.h"
%}
#else
%header %{
#include <GL/gl.h>
%}
#endif

/* This is what SWIG parses to generate the wrapper */
#ifdef SWIGMAC
%include "/System/Library/Frameworks/OpenGL.framework/Headers/gl.h"
#else
%include <GL/gl.h>
#endif

#ifdef RBOGL_UNTYPED
%include "gl_untyped.i"
#endif
