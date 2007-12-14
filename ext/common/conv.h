/*
 * Copyright (C) 2007 Jan Dvorak <jan.dvorak@kraxnet.cz>
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

/* Functions and macros for datatype conversion between Ruby and C */

/* -------------------------------------------------------------------- */
#undef NUM2DBL
#define NUM2DBL num2double
static inline double
num2double(val)
VALUE val;
{
	if (FIXNUM_P(val))
		return (GLdouble) FIX2LONG(val);

	if (TYPE(val) == T_FLOAT)
		return RFLOAT(val)->value;

	return NUM2DBL(val);
}


#define GLBOOL2RUBY(x) (x)==GL_TRUE? Qtrue : Qfalse
#define RUBYBOOL2GL(x) (x)==Qtrue? GL_TRUE : GL_FALSE

/* -------------------------------------------------------------------- */
#define ARY2INTEGRAL(_type_,_convert_) \
static inline int ary2c##_type_( arg, cary, maxlen ) \
VALUE arg; \
GL##_type_ cary[]; \
int maxlen; \
{ \
    int i; \
    struct RArray* ary; \
    VALUE entry; \
    ary = RARRAY(rb_Array(arg)); \
    if (maxlen < 1) \
        maxlen = ary->len; \
    else \
        maxlen = maxlen < ary->len ? maxlen : ary->len; \
    for (i=0; i < maxlen; i++) \
    { \
        entry = rb_ary_entry((VALUE)ary,i); \
        cary[i] = (GL##_type_)_convert_(entry); \
    } \
    return i; \
}

ARY2INTEGRAL(int,NUM2INT)
ARY2INTEGRAL(uint,NUM2UINT)
ARY2INTEGRAL(byte,NUM2INT)
ARY2INTEGRAL(ubyte,NUM2INT)
ARY2INTEGRAL(short,NUM2INT)
ARY2INTEGRAL(ushort,NUM2INT)
ARY2INTEGRAL(boolean,NUM2INT)
#undef ARY2INTEGRAL

/* -------------------------------------------------------------------- */
static inline int ary2cflt(arg, cary, maxlen)
VALUE arg;
float cary[];
int maxlen;
{
    int i;
    struct RArray* ary;
    ary = RARRAY(rb_Array(arg));
    if (maxlen < 1)
        maxlen = ary->len;
    else
        maxlen = maxlen < ary->len ? maxlen : ary->len;
    for (i=0; i < maxlen; i++)
        cary[i] = (float)NUM2DBL(rb_ary_entry((VALUE)ary,i));
    return i;
}

/* -------------------------------------------------------------------- */
static inline int ary2cdbl(arg, cary, maxlen)
VALUE arg;
double cary[];
int maxlen;
{
    int i;
    struct RArray* ary;
    ary = RARRAY(rb_Array(arg));
    if (maxlen < 1)
        maxlen = ary->len;
    else
        maxlen = maxlen < ary->len ? maxlen : ary->len;
    for (i=0; i < maxlen; i++)
        cary[i] = NUM2DBL(rb_ary_entry((VALUE)ary,i));
    return i;
}

/* Converts either array or object responding to #to_a to C-style array */
#define ARY2CMAT(_type_) \
static inline void ary2cmat##_type_(rary, cary, cols, rows) \
VALUE rary; \
_type_ cary[]; \
int cols,rows; \
{ \
	int i; \
\
	rary = rb_Array(rary); \
	rary = rb_funcall(rary,rb_intern("flatten"),0); \
\
	if (RARRAY(rary)->len != cols*rows) \
		rb_raise(rb_eArgError, "passed array/matrix must have %i*%i elements",cols,rows); \
\
	for (i=0; i < cols*rows; i++) \
		cary[i] = (_type_) NUM2DBL(rb_ary_entry(rary,i)); \
}

ARY2CMAT(double)
ARY2CMAT(float)
#undef ARY2CMAT
