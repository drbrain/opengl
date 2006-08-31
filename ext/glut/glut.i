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

%module GLUT

%module GL
#ifdef SWIGMAC
%header %{
#include "/System/Library/Frameworks/GLUT.framework/Headers/glut.h"
%}
#else
%header %{
#include <GL/freeglut_std.h>
%}
#endif

%include "glut_init.i"
%include "glut_callbacks.i"

#ifdef SWIGMAC
%include "/System/Library/Frameworks/GLUT.framework/Headers/glut.h"
#else
%include <GL/freeglut_std.h>
#endif
