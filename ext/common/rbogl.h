/*
 * Last edit by previous maintainer:
 * 2000/01/06 16:37:43, kusano
 *
 * Copyright (C) 1999 - 2005 Yoshi <yoshi@giganet.net>
 * Copyright (C) 2006 John M. Gabriele <jmg3000@gmail.com>
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

#ifndef _RBOGL_H_
#define _RBOGL_H_

#include <ruby.h>

typedef struct RArray RArray;

extern VALUE cProc;

int   ary2cint( VALUE, int[], int );
int   ary2cuint( VALUE, GLuint[], int );
int   ary2cshort( VALUE, GLshort[], int );
int   ary2cushort( VALUE, GLushort[], int );
int   ary2cbyte( VALUE, GLbyte[], int );
int   ary2cubyte( VALUE, GLubyte[], int );
int   ary2cboolean( VALUE, GLboolean[], int );
int   ary2cdbl( VALUE, double[], int );
int   ary2cflt( VALUE, float[], int );
void  mary2ary( VALUE, VALUE );
void  ary2cmat4x4dbl( VALUE, double[] );
void  ary2cmat4x4flt( VALUE, float[] );
VALUE allocate_buffer_with_string( int );

#ifndef NUM2DBL
double num2double( VALUE );
#define _NO_NUM2DBL_
#define NUM2DBL(_val) num2double(_val) 
#endif /* NUM2DBL */

int gltype_size(GLenum type);
int glformat_size(GLenum format);

#endif /* _RBOGL_H_ */
