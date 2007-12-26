/*
 * Last edit by previous maintainer:
 * 2003/10/25 15:25:05, yoshi
 *
 * Copyright (C) 1999 - 2005 Yoshi <yoshi@giganet.net>
 * Copyright (C) 2006 John M. Gabriele <jmg3000@gmail.com>
 *
 * This program is distributed under the terms of the MIT license.
 * See the included COPYRIGHT file for the terms of this license.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "../common/common.h"

static VALUE module;

VALUE Class_GLUError;

void glu_init_enums(VALUE);

typedef GLUtesselator tesselatorObj;

/* pointers passed to gluNurbsCurve/Surface etc.,
  - some implementations (Mesa) needs these to be valid
  at EndCurve/Surface etc. call., so we store them here
  and free them after that call */

struct glu_MesaStack {
	int len;
	GLfloat **ptr;
};

static struct glu_MesaStack gms = {0, NULL};

struct nurbsdata {
	GLUnurbsObj *nobj;
	VALUE n_ref;
};
struct tessdata {
	tesselatorObj *tobj;
	VALUE t_ref;
};

struct quaddata {
	GLUquadricObj *qobj;
	VALUE q_ref;
};

static VALUE cNurbs;
static VALUE cTess;
static VALUE cQuad;

#define REF_LAST    15

#define GetNURBS(obj, ndata) {\
	Data_Get_Struct(obj, struct nurbsdata, ndata);\
	if (ndata->nobj == NULL) rb_raise(rb_eRuntimeError, "Nurbs Object already deleted!");\
}

#define GetTESS(obj, tdata) {\
	Data_Get_Struct(obj, struct tessdata, tdata);\
	if (tdata->tobj == NULL) rb_raise(rb_eRuntimeError, "Triangulator Object already deleted!");\
}

#define GetQUAD(obj, qdata) {\
	Data_Get_Struct(obj, struct quaddata, qdata);\
	if (qdata->qobj == NULL) rb_raise(rb_eRuntimeError, "Quadric Object already deleted!");\
}

static ID callId;
static ID refId;

/*
 * GLU Implementation
 */

/*
 * Nurbs
 */
/* from nurbscrv.c */
static int
get_curve_dim(type)
GLenum type;
{
	switch(type)
	{
		case GL_MAP1_VERTEX_3:          return 3;
		case GL_MAP1_VERTEX_4:          return 4;  
		case GL_MAP1_INDEX:             return 1;
		case GL_MAP1_COLOR_4:           return 4;
		case GL_MAP1_NORMAL:            return 3;
		case GL_MAP1_TEXTURE_COORD_1:   return 1;
		case GL_MAP1_TEXTURE_COORD_2:   return 2;
		case GL_MAP1_TEXTURE_COORD_3:   return 3;
		case GL_MAP1_TEXTURE_COORD_4:   return 4;
		default:
			rb_raise(rb_eArgError,"Unknown curve type '%i'",type);
	}
	return 0; /* never gets here */
}
/* from nurbssrf.c */
static int
get_surface_dim(GLenum type)
{
	switch(type)
	{
		case GL_MAP2_VERTEX_3:          return 3;
		case GL_MAP2_VERTEX_4:          return 4;
		case GL_MAP2_INDEX:             return 1;
		case GL_MAP2_COLOR_4:           return 4;
		case GL_MAP2_NORMAL:            return 3;
		case GL_MAP2_TEXTURE_COORD_1:   return 1; 
		case GL_MAP2_TEXTURE_COORD_2:   return 2;
		case GL_MAP2_TEXTURE_COORD_3:   return 3;
		case GL_MAP2_TEXTURE_COORD_4:   return 4;
		default:
			rb_raise(rb_eArgError,"Unknown surface type '%i'",type);
	}
	return 0; /* never gets here */
}

VALUE GLUError_initialize(VALUE obj,VALUE message, VALUE error_id)
{
	rb_call_super(1, &message);
	rb_iv_set(obj, "@id", error_id);

	return obj;
}

void check_for_gluerror(GLenum error)
{
	char *error_string = "";
	VALUE exc;
	
	/* no error */
	if (error==0)
		return;
	
	switch(error) {
		case GLU_INVALID_ENUM: error_string = "invalid enumerant"; break;
		case GLU_INVALID_VALUE: error_string = "invalid value"; break;
		case GLU_INVALID_OPERATION: error_string = "invalid operation"; break;
		case GLU_OUT_OF_MEMORY: error_string = "out of memory"; break;
		default: error_string = "unknown error"; break;
	}

	exc = rb_funcall(Class_GLUError, rb_intern("new"), 2, rb_str_new2(error_string), RETCONV_GLenum(error));
	rb_funcall(rb_cObject, rb_intern("raise"), 1, exc);
}

/*
 * NURBS API
 */
static VALUE n_current;

static void
free_nurbs(ndata)
struct nurbsdata *ndata;
{
	if (ndata->nobj) gluDeleteNurbsRenderer(ndata->nobj);
		ndata->nobj = NULL;
	ndata->n_ref = Qnil;
}
static void
mark_nurbs(ndata)
struct nurbsdata* ndata;
{
	if (ndata->nobj)
		rb_gc_mark(ndata->n_ref);
}

static void CALLBACK
n_error(errorno)
GLenum errorno;
{
	VALUE nurbs;
	struct nurbsdata *ndata;
	nurbs = rb_ary_entry(n_current, -1);
	if (nurbs == Qnil)
		return;
	GetNURBS(nurbs, ndata);
	rb_funcall(rb_ary_entry(ndata->n_ref, GLU_ERROR), callId, 1, INT2NUM(errorno));
}

static VALUE
glu_NurbsCallback(obj, arg1, arg2, arg3)
VALUE obj, arg1, arg2, arg3;
{
	struct nurbsdata* ndata;
	GLenum type;
	GetNURBS(arg1, ndata);
	type = (GLenum)NUM2INT(arg2);
	if (!rb_obj_is_kind_of(arg3,rb_cProc) && !NIL_P(arg3))
		rb_raise(rb_eTypeError, "gluNurbsCallback needs Proc Object:%s",rb_class2name(CLASS_OF(arg3)));

	if (type!=GLU_ERROR)
		return Qnil;

	rb_ary_store(ndata->n_ref, type, arg3);
	if (NIL_P(arg3))
		gluNurbsCallback(ndata->nobj, type, NULL);
	else
		gluNurbsCallback(ndata->nobj, type, n_error);

	CHECK_GLERROR	
	return Qnil;
}


static VALUE
glu_NewNurbsRenderer(obj)
VALUE obj;
{
	VALUE ret;
	struct nurbsdata *ndata;
	ret = Data_Make_Struct(cNurbs, struct nurbsdata, mark_nurbs, free_nurbs, ndata);
	ndata->nobj = gluNewNurbsRenderer();
	ndata->n_ref = rb_ary_new2(REF_LAST);
	CHECK_GLERROR	
	return ret;
}
static VALUE
glu_DeleteNurbsRenderer(obj, arg1)
VALUE obj, arg1;
{
	struct nurbsdata *ndata;
	GetNURBS(arg1, ndata);
	free_nurbs(ndata);
	CHECK_GLERROR	
	return Qnil;
}
static VALUE
glu_NurbsProperty(obj, arg1, arg2, arg3)
VALUE obj, arg1, arg2, arg3;
{
	struct nurbsdata *ndata;
	GLenum property;
	GLfloat value;
	GetNURBS(arg1, ndata);
	property = (GLenum)NUM2INT(arg2);
	value = (GLfloat)NUM2DBL(arg3);
	gluNurbsProperty(ndata->nobj, property, value);
	CHECK_GLERROR	
	return Qnil;
}
static VALUE
glu_GetNurbsProperty(obj, arg1, arg2)
VALUE obj, arg1, arg2;
{
	struct nurbsdata *ndata;
	GLenum property;
	GLfloat value;
	GetNURBS(arg1, ndata);
	property = (GLenum)NUM2INT(arg2);
	gluGetNurbsProperty(ndata->nobj, property, &value);
	CHECK_GLERROR	
	return cond_GLBOOL2RUBY_F(property,value);
}
static VALUE
glu_BeginCurve(obj, arg1)
VALUE obj, arg1;
{
	struct nurbsdata *ndata;
	GetNURBS(arg1, ndata);
	rb_ary_push(n_current, arg1);
	gluBeginCurve(ndata->nobj);
	CHECK_GLERROR	
	return Qnil;
}
static VALUE
glu_EndCurve(obj, arg1)
VALUE obj, arg1;
{
	struct nurbsdata *ndata;
	GetNURBS(arg1, ndata);
	gluEndCurve(ndata->nobj);

	for (;gms.len>0;gms.len--)
		free(gms.ptr[gms.len-1]);
	free(gms.ptr);
	gms.ptr = NULL;

	rb_ary_pop(n_current);

	CHECK_GLERROR	
	return Qnil;
}
static VALUE
glu_NurbsCurve(argc,argv,obj)
int argc;
VALUE *argv;
VALUE obj;
{
	struct nurbsdata *ndata;
	GLint uknot_count;
	GLfloat *uknot;
	GLint u_stride;
	GLint uorder;
	GLfloat *ctlarray;
	GLenum type;
	
	VALUE args[7];
	VALUE ary_ctl1;
	
	switch (rb_scan_args(argc, argv, "52", &args[0], &args[1], &args[2], &args[3], &args[4], &args[5], &args[6])) {
		case 5:
			uknot_count = RARRAY(args[1])->len;
			uorder = (GLenum)NUM2INT(args[3]);
			type = (GLenum)NUM2INT(args[4]);
			u_stride = get_curve_dim(type);
		
			uknot = ALLOC_N(GLfloat, uknot_count);
			ary2cflt(args[1], uknot, uknot_count);

			ary_ctl1 = rb_ary_new();
			mary2ary(args[2], ary_ctl1); /* flatten */
			break;
		case 7:
			uknot_count = (GLint)NUM2INT(args[1]);
			u_stride = (GLint)NUM2INT(args[3]);
			uorder = (GLint)NUM2INT(args[5]);
			type = (GLenum)NUM2INT(args[6]);

			uknot = ALLOC_N(GLfloat, uknot_count);
			ary2cflt(args[2], uknot, uknot_count);

			ary_ctl1 = rb_ary_new();
			mary2ary(args[4], ary_ctl1); /* flatten */
			break;
		default:
			rb_raise(rb_eArgError, "gluNurbsCurve needs 5 or 7 arguments");
	}
	ctlarray = ALLOC_N(GLfloat, u_stride*(uknot_count-uorder));
	ary2cflt((VALUE)ary_ctl1, ctlarray, (uknot_count-uorder)*u_stride);

	GetNURBS(args[0], ndata);
	gluNurbsCurve(ndata->nobj, uknot_count, uknot, u_stride, ctlarray, uorder, type);

	/* store the pointers */
	gms.ptr = REALLOC_N(gms.ptr, GLfloat*, gms.len+=2);
	gms.ptr[gms.len - 2] = uknot;
	gms.ptr[gms.len - 1] = ctlarray;
	CHECK_GLERROR	
	return Qnil;
}
static VALUE
glu_BeginSurface(obj, arg1)
VALUE obj, arg1;
{
	struct nurbsdata *ndata;
	GetNURBS(arg1, ndata);
	rb_ary_push(n_current, arg1);
	gluBeginSurface(ndata->nobj);
	CHECK_GLERROR	
	return Qnil;
}
static VALUE
glu_EndSurface(obj, arg1)
VALUE obj, arg1;
{
	struct nurbsdata *ndata;
	GetNURBS(arg1, ndata);
	gluEndSurface(ndata->nobj);
	
	for(; gms.len>0; gms.len--)
		free(gms.ptr[gms.len-1]);
	free(gms.ptr);
	gms.ptr = NULL;

	rb_ary_pop(n_current);
	
	CHECK_GLERROR	
	return Qnil;
}

static VALUE
glu_NurbsSurface(argc, argv, obj)
int argc;
VALUE *argv;
VALUE obj;
{
	struct nurbsdata *ndata;
	GLint sknot_count;
	GLfloat *sknot;
	GLint tknot_count;
	GLfloat *tknot;
	GLint s_stride;
	GLint t_stride;
	GLfloat *ctlarray;
	GLint sorder;
	GLint torder;
	GLenum type;
	
	VALUE args[11];
	VALUE ary_ctl1;
	int type_len;
	
	switch (rb_scan_args(argc, argv, "74", &args[0], &args[1], &args[2], &args[3], &args[4], &args[5], &args[6], &args[7], &args[8], &args[9], &args[10])) {
		case 7:
			sknot_count = RARRAY(args[1])->len;
			sknot = ALLOC_N(GLfloat, sknot_count);
			ary2cflt(args[1], sknot, sknot_count);

			tknot_count = RARRAY(args[2])->len;
			tknot = ALLOC_N(GLfloat, tknot_count);
			ary2cflt(args[2], tknot, tknot_count);

			sorder = (GLint)NUM2INT(args[4]);
			torder = (GLint)NUM2INT(args[5]);
			type = (GLenum)NUM2INT(args[6]);

			t_stride = get_surface_dim(type);
			s_stride = t_stride * sorder;

			ctlarray = ALLOC_N(GLfloat, (sknot_count-sorder)*(tknot_count-torder)*t_stride);
			ary_ctl1 = rb_ary_new();
			mary2ary(args[3], ary_ctl1); /* flatten */
			ary2cflt(ary_ctl1, ctlarray, (sknot_count-sorder)*(tknot_count-torder)*t_stride);
			break;
		case 11:
			sknot_count = (GLint)NUM2INT(args[1]);
			sknot = ALLOC_N(GLfloat, sknot_count);
			ary2cflt(args[2], sknot, sknot_count);
			
			tknot_count = (GLint)NUM2INT(args[3]);
			tknot = ALLOC_N(GLfloat, tknot_count);
			ary2cflt(args[4], tknot, tknot_count);
			
			s_stride = (GLint)NUM2INT(args[5]);
			t_stride = (GLint)NUM2INT(args[6]);
			sorder = (GLint)NUM2INT(args[8]);
			torder = (GLint)NUM2INT(args[9]);
			type = (GLint)NUM2INT(args[10]);
			type_len = get_surface_dim(type);
			
			ctlarray = ALLOC_N(GLfloat, (sknot_count-sorder)*(tknot_count-torder)*type_len);
			
			ary_ctl1 = rb_ary_new();
			mary2ary(args[7], ary_ctl1); /* flatten */
			ary2cflt(ary_ctl1, ctlarray, (sknot_count-sorder)*(tknot_count-torder)*type_len);
			break;
		default:
			rb_raise(rb_eArgError, "gluNurbsSurface needs 7 or 11 arguments");
			return Qnil; /* not reached */
	}
	GetNURBS(args[0], ndata);
	gluNurbsSurface(ndata->nobj, sknot_count, sknot, tknot_count, tknot,
	s_stride, t_stride, ctlarray, sorder, torder, type);
	
	/* store the pointers */
	
	gms.ptr = REALLOC_N(gms.ptr, GLfloat*, gms.len+=3);
	gms.ptr[gms.len-3] = sknot;
	gms.ptr[gms.len-2] = tknot;
	gms.ptr[gms.len-1] = ctlarray;
	
	CHECK_GLERROR	
	return Qnil;
}
static VALUE
glu_BeginTrim(obj, arg1)
VALUE obj, arg1;
{
	struct nurbsdata *ndata;
	GetNURBS(arg1, ndata);
	rb_ary_push(n_current, arg1);
	gluBeginTrim(ndata->nobj);
	CHECK_GLERROR	
	return Qnil;
}
static VALUE
glu_EndTrim(obj, arg1)
VALUE obj, arg1;
{
	struct nurbsdata *ndata;
	GetNURBS(arg1, ndata);
	gluEndTrim(ndata->nobj);
	rb_ary_pop(n_current);
	CHECK_GLERROR	
	return Qnil;
}
static VALUE
glu_PwlCurve(argc, argv, obj)
int argc;
VALUE *argv;
VALUE obj;
{
	struct nurbsdata *ndata;
	GLint count;
	GLfloat *array;
	GLint stride;
	GLenum type;
	
	VALUE args[5];
	VALUE ary_ctl1;
	
	switch (rb_scan_args(argc, argv, "32", &args[0], &args[1], &args[2], &args[3], &args[4])) {
		case 3:
			count = RARRAY(args[1])->len;
			type = NUM2INT(args[2]);
			stride = (type == GLU_MAP1_TRIM_2 ? 2 : 3);

			array = ALLOC_N(GLfloat, count*stride);
			ary_ctl1 = rb_ary_new();
			mary2ary(args[1], ary_ctl1); /* flatten */
			ary2cflt(ary_ctl1, array, count*stride);
			break;
		case 5:
			count = NUM2INT(args[1]);
			stride = NUM2INT(args[3]);
			type = NUM2INT(args[4]);

			array = ALLOC_N(GLfloat, count*stride);
			ary_ctl1 = rb_ary_new();
			mary2ary(args[2], ary_ctl1); /* flatten */
			ary2cflt(ary_ctl1, array, count*stride);
			break;
		default:
			rb_raise(rb_eArgError, "gluPwlCurve needs 3 or 5 arguments");
			return Qnil; /* not reached */
	}

	GetNURBS(args[0], ndata);
	gluPwlCurve(ndata->nobj, count, array, stride, type);
	free(array);
	CHECK_GLERROR	
	return Qnil;
}

static VALUE glu_LoadSamplingMatrices(obj,arg1,arg2,arg3,arg4)
VALUE obj, arg1,arg2,arg3,arg4;
{
	struct nurbsdata *ndata;
	GLfloat mdl_mtx[4*4];
	GLfloat persp_mtx[4*4];
	GLint viewport[4];

	GetNURBS(arg1, ndata);
	ary2cmatfloat(arg2,mdl_mtx,4,4);
	ary2cmatfloat(arg3,persp_mtx,4,4);
	ary2cint(arg4,viewport,4);

	gluLoadSamplingMatrices(ndata->nobj,mdl_mtx,persp_mtx,viewport);

	CHECK_GLERROR	
	return Qnil;
}

/*
 * Tesselation API
 */
static VALUE t_current;
#define TESS_DATA   0
#define TESS_BEGIN  1
#define TESS_VERTEX 2
#define TESS_END    3
#define TESS_ERROR  4
#define TESS_EDGE_FLAG   5
#define TESS_OUTDATA     6
#define TESS_COMBINE     7
#define TESS_BEGIN_DATA  8
#define TESS_VERTEX_DATA 9
#define TESS_END_DATA    10
#define TESS_ERROR_DATA  11
#define TESS_EDGE_FLAG_DATA   12
#define TESS_COMBINE_DATA    13
#define TESS_USERDATA   14

static void
mark_tess(tdata)
struct tessdata* tdata;
{
	if (tdata->tobj)
		rb_gc_mark(tdata->t_ref);
}
static void
free_tess(tdata)
struct tessdata *tdata;
{
	if (tdata->tobj)
		gluDeleteTess(tdata->tobj);
	tdata->t_ref = Qnil;
	tdata->tobj = NULL;
}
static VALUE
glu_NewTess(obj)
VALUE obj;
{
	VALUE ret;
	struct tessdata *tdata;
	ret = Data_Make_Struct(cTess, struct tessdata, mark_tess, free_tess, tdata);
	tdata->tobj = gluNewTess();
	tdata->t_ref = rb_ary_new2(REF_LAST);
	CHECK_GLERROR	
	return ret;
}
static VALUE
glu_DeleteTess(obj, arg1)
VALUE obj, arg1;
{
	struct tessdata *tdata;
	GetTESS(arg1, tdata);
	free_tess(tdata);
	CHECK_GLERROR	
	return Qnil;
}

/* tess* callback function wrappers */
#define TESS_CALLBACK_COMMON \
VALUE tess; \
struct tessdata *tdata; \
tess = rb_ary_entry(t_current, -1); \
if (tess == Qnil) \
	return; \
GetTESS(tess, tdata);

static void CALLBACK
t_begin(type)
GLenum type;
{
	TESS_CALLBACK_COMMON
	rb_funcall(rb_ary_entry(tdata->t_ref, TESS_BEGIN), callId, 1, INT2NUM(type));
}
static void CALLBACK
t_edgeFlag(flag)
GLboolean flag;
{
	TESS_CALLBACK_COMMON
	rb_funcall(rb_ary_entry(tdata->t_ref, TESS_EDGE_FLAG), callId, 1, GLBOOL2RUBY(flag));
}
static void CALLBACK
t_vertex(data)
void* data;
{
	TESS_CALLBACK_COMMON
	rb_funcall(rb_ary_entry(tdata->t_ref, TESS_VERTEX), callId, 1, data);
}
static void CALLBACK
t_end()
{
	TESS_CALLBACK_COMMON
	rb_funcall(rb_ary_entry(tdata->t_ref, TESS_END), callId, 0);
}
static void CALLBACK
t_error(errorno)
GLenum errorno;
{
	TESS_CALLBACK_COMMON
	rb_funcall(rb_ary_entry(tdata->t_ref, TESS_ERROR), callId, 1, INT2NUM(errorno));
}
static void CALLBACK
t_begin_data(type, user_data)
GLenum type;
void* user_data;
{
	TESS_CALLBACK_COMMON
	rb_funcall(rb_ary_entry(tdata->t_ref, TESS_BEGIN_DATA), callId, 2, INT2NUM(type), user_data);
}
static void CALLBACK
t_edgeFlag_data(flag, user_data)
GLboolean flag;
void* user_data;
{
	TESS_CALLBACK_COMMON
	rb_funcall(rb_ary_entry(tdata->t_ref, TESS_EDGE_FLAG_DATA), callId, 2, GLBOOL2RUBY(flag), user_data);
}
static void CALLBACK
t_vertex_data(data, user_data)
void* data;
void* user_data;
{
	TESS_CALLBACK_COMMON
	rb_funcall(rb_ary_entry(tdata->t_ref, TESS_VERTEX_DATA), callId, 2, data, user_data);
}
static void CALLBACK
t_end_data(user_data)
void* user_data;
{
	TESS_CALLBACK_COMMON
	rb_funcall(rb_ary_entry(tdata->t_ref, TESS_END_DATA), callId, 1, user_data);
}
static void CALLBACK
t_error_data(errorno, user_data)
GLenum errorno;
void* user_data;
{
	TESS_CALLBACK_COMMON
	rb_funcall(rb_ary_entry(tdata->t_ref, TESS_ERROR_DATA), callId, 2, INT2NUM(errorno), user_data);
}

static void CALLBACK
t_combine(coords, vertex_data, weight, outData)
GLdouble coords[3];
void* vertex_data[4];
GLfloat weight[4];
void** outData;
{
	VALUE rb_coord, rb_vertex_data, rb_weight;
	int i;
	TESS_CALLBACK_COMMON

	rb_coord = rb_ary_new2(3);
	for (i = 0; i < 3; i++)
			rb_ary_store(rb_coord, i, rb_float_new(coords[i]));
	rb_vertex_data = rb_ary_new2(4);
	for (i = 0; i < 4; i++)
			rb_ary_store(rb_vertex_data, i, (VALUE)vertex_data[i]);
	rb_weight = rb_ary_new2(4);
	for (i = 0; i < 4; i++)
			rb_ary_store(rb_weight, i, rb_float_new(weight[i]));
	*outData = (void*)rb_funcall(rb_ary_entry(tdata->t_ref, TESS_COMBINE), callId, 3, rb_coord, rb_vertex_data, rb_weight);
	rb_ary_push(rb_ary_entry(tdata->t_ref, TESS_OUTDATA), (VALUE)*outData);
}

static void CALLBACK
t_combine_data(coords, vertex_data, weight, outData, user_data)
GLdouble coords[3];
void* vertex_data[4];
GLfloat weight[4];
void** outData;
void* user_data;
{
	VALUE rb_coord, rb_vertex_data, rb_weight;
	int i;
	TESS_CALLBACK_COMMON
	
	rb_coord = rb_ary_new2(3);
	for (i = 0; i < 3; i++)
		rb_ary_store(rb_coord, i, rb_float_new(coords[i]));
	rb_vertex_data = rb_ary_new2(4);
	for (i = 0; i < 4; i++)
		rb_ary_store(rb_vertex_data, i, (VALUE)vertex_data[i]);
	rb_weight = rb_ary_new2(4);
	for (i = 0; i < 4; i++)
		rb_ary_store(rb_weight, i, rb_float_new(weight[i]));

	*outData = (void*)rb_funcall(rb_ary_entry(tdata->t_ref, TESS_COMBINE_DATA), callId, 4, rb_coord, rb_vertex_data, rb_weight, (VALUE)user_data);

	rb_ary_push(rb_ary_entry(tdata->t_ref, TESS_OUTDATA), (VALUE)*outData);
}

#undef TESS_CALLBACK_COMMON

static VALUE
glu_TessProperty(obj, arg1, arg2, arg3)
VALUE obj, arg1, arg2;
{
	struct tessdata* tdata;
	GLenum property;
	GLdouble value;
	GetTESS(arg1, tdata);
	property = (GLenum)NUM2INT(arg2);
	value = (GLdouble)NUM2DBL(arg3);
	gluTessProperty(tdata->tobj, property, value);
	CHECK_GLERROR	
	return Qnil;
}
static VALUE
glu_GetTessProperty(obj, arg1, arg2)
VALUE obj, arg1, arg2;
{
	struct tessdata* tdata;
	GLenum property;
	GLdouble value;
	GetTESS(arg1, tdata);
	property = (GLenum)NUM2INT(arg2);
	gluGetTessProperty(tdata->tobj, property, &value);
	CHECK_GLERROR	
	return cond_GLBOOL2RUBY_F(property,value);
}
static VALUE
glu_TessNormal(obj, arg1, arg2, arg3, arg4)
VALUE obj, arg1, arg2, arg3, arg4;
{
	struct tessdata* tdata;
	GLdouble x, y, z;
	GetTESS(arg1, tdata);
	x = (GLdouble)NUM2DBL(arg2);
	y = (GLdouble)NUM2DBL(arg3);
	z = (GLdouble)NUM2DBL(arg4);
	gluTessNormal(tdata->tobj, x, y, z);
	CHECK_GLERROR	
	return Qnil;
}
static VALUE
glu_TessBeginPolygon(obj, arg1, arg2)
VALUE obj, arg1, arg2;
{
	struct tessdata* tdata;
	GetTESS(arg1, tdata);
	rb_ary_store(tdata->t_ref, TESS_USERDATA, arg2);
	rb_ary_store(tdata->t_ref, TESS_OUTDATA, rb_ary_new());
	rb_ary_store(tdata->t_ref, TESS_DATA, rb_ary_new());
	rb_ary_push(t_current, arg1);
	gluTessBeginPolygon(tdata->tobj, (void*)arg2);
	CHECK_GLERROR	
	return Qnil;
}
static VALUE
glu_TessEndPolygon(obj, arg1)
VALUE obj, arg1;
{
	struct tessdata* tdata;
	GetTESS(arg1, tdata);
	gluTessEndPolygon(tdata->tobj);
	rb_ary_store(tdata->t_ref, TESS_USERDATA, Qnil);
	rb_ary_store(tdata->t_ref, TESS_OUTDATA, Qnil);
	rb_ary_store(tdata->t_ref, TESS_DATA, Qnil);
	rb_ary_pop(t_current);
	CHECK_GLERROR	
	return Qnil;
}
static VALUE
glu_TessBeginContour(obj, arg1)
VALUE obj, arg1;
{
	struct tessdata* tdata;
	GetTESS(arg1, tdata);
	gluTessBeginContour(tdata->tobj);
	CHECK_GLERROR	
	return Qnil;
}
static VALUE
glu_TessEndContour(obj, arg1)
VALUE obj, arg1;
{
	struct tessdata* tdata;
	GetTESS(arg1, tdata);
	gluTessEndContour(tdata->tobj);
	CHECK_GLERROR	
	return Qnil;
}

#define TESS_CALLBACK_CASE(_type_,_function_) \
    case GLU_##_type_: \
            rb_ary_store(tdata->t_ref, _type_, arg3); \
            if (NIL_P(arg3)) \
                gluTessCallback(tdata->tobj, type, NULL); \
            else \
                gluTessCallback(tdata->tobj, type, _function_); \
        break;

static VALUE
glu_TessCallback(obj, arg1, arg2, arg3)
VALUE obj, arg1, arg2, arg3;
{
	struct tessdata* tdata;
	GLenum type;
	GetTESS(arg1, tdata);
	type = (GLenum)NUM2INT(arg2);
	if (!rb_obj_is_kind_of(arg3,rb_cProc) && !NIL_P(arg3))
		rb_raise(rb_eTypeError, "gluTessCallback needs Proc Object:%s",rb_class2name(CLASS_OF(arg3)));
	
	switch (type) {
		TESS_CALLBACK_CASE(TESS_BEGIN,t_begin)
		TESS_CALLBACK_CASE(TESS_BEGIN_DATA,t_begin_data)
		TESS_CALLBACK_CASE(TESS_EDGE_FLAG,t_edgeFlag)
		TESS_CALLBACK_CASE(TESS_EDGE_FLAG_DATA,t_edgeFlag_data)
		TESS_CALLBACK_CASE(TESS_VERTEX,t_vertex)
		TESS_CALLBACK_CASE(TESS_VERTEX_DATA,t_vertex_data)
		TESS_CALLBACK_CASE(TESS_END,t_end)
		TESS_CALLBACK_CASE(TESS_END_DATA,t_end_data)
		TESS_CALLBACK_CASE(TESS_ERROR,t_error)
		TESS_CALLBACK_CASE(TESS_ERROR_DATA,t_error_data)
		TESS_CALLBACK_CASE(TESS_COMBINE,t_combine)
		TESS_CALLBACK_CASE(TESS_COMBINE_DATA,t_combine_data)
	}
	CHECK_GLERROR	
	return Qnil;
}
#undef TESS_CALLBACK_CASE

static VALUE
glu_BeginPolygon(obj, arg1)
VALUE obj, arg1;
{
	struct tessdata* tdata;
	GetTESS(arg1, tdata);
	rb_ary_store(tdata->t_ref, TESS_DATA, rb_ary_new());
	rb_ary_push(t_current, arg1);
	gluBeginPolygon(tdata->tobj);
	CHECK_GLERROR	
	return Qnil;
}
static VALUE
glu_TessVertex(obj, arg1, arg2, arg3)
VALUE obj, arg1, arg2, arg3;
{
	struct tessdata* tdata;
	GLdouble v[3] = {0.0,0.0,0.0};
	GetTESS(arg1, tdata);
	rb_ary_push(rb_ary_entry(tdata->t_ref, TESS_DATA), arg3);
	Check_Type(arg2,T_ARRAY);
	ary2cdbl(arg2, v, 3);
	gluTessVertex(tdata->tobj, v,(void *)arg3);
	CHECK_GLERROR	
	return Qnil;
}
static VALUE
glu_NextContour(obj, arg1, arg2)
VALUE obj, arg1, arg2;
{
	struct tessdata* tdata;
	GLenum type;
	GetTESS(arg1, tdata);
	type = (GLenum)NUM2INT(arg2);
	gluNextContour(tdata->tobj, type);
	CHECK_GLERROR	
	return Qnil;
}
static VALUE
glu_EndPolygon(obj, arg1)
VALUE obj, arg1;
{
	struct tessdata* tdata;
	GetTESS(arg1, tdata);
	gluEndPolygon(tdata->tobj);
	rb_ary_store(tdata->t_ref, TESS_DATA, Qnil);
	rb_ary_pop(t_current);
	CHECK_GLERROR	
	return Qnil;
}

/*
 * Quadric API
 */
static VALUE q_current;

static void CALLBACK
q_error(errorno)
GLenum errorno;
{
	VALUE quad;
	struct quaddata *qdata;
	quad = rb_ary_entry(q_current, -1);
	if (quad == Qnil)
		return;
	GetQUAD(quad, qdata);
	rb_funcall(rb_ary_entry(qdata->q_ref, GLU_ERROR), callId, 1, INT2NUM(errorno));
}

static VALUE
glu_QuadricCallback(obj, arg1, arg2, arg3)
VALUE obj, arg1, arg2, arg3;
{
	struct quaddata* qdata;
	GLenum type;
	GetQUAD(arg1, qdata);
	type = (GLenum)NUM2INT(arg2);
	if (!rb_obj_is_kind_of(arg3,rb_cProc) && !NIL_P(arg3))
		rb_raise(rb_eTypeError, "gluQuadricCallback needs Proc Object:%s",rb_class2name(CLASS_OF(arg3)));

	CHECK_GLERROR	
	if (type!=GLU_ERROR)
		return Qnil;

	rb_ary_store(qdata->q_ref, type, arg3);
	if (NIL_P(arg3))
		gluQuadricCallback(qdata->qobj, type, NULL);
	else
		gluQuadricCallback(qdata->qobj, type, q_error);
	
	CHECK_GLERROR	
	return Qnil;
}

static void
free_quad(qdata)
struct quaddata *qdata;
{
  if (qdata->qobj) gluDeleteQuadric(qdata->qobj);
  qdata->qobj = NULL;
	qdata->q_ref = Qnil;
}
static void
mark_quad(qdata)
struct quaddata* qdata;
{
	if (qdata->qobj)
		rb_gc_mark(qdata->q_ref);
}
static VALUE
glu_NewQuadric(obj)
VALUE obj;
{
	VALUE ret;
	struct quaddata *qdata;
	ret = Data_Make_Struct(cQuad, struct quaddata, mark_quad, free_quad, qdata);
	qdata->qobj = gluNewQuadric();
	qdata->q_ref = rb_ary_new2(REF_LAST);
	CHECK_GLERROR	
	return ret;
}
static VALUE
glu_DeleteQuadric(obj, arg1)
VALUE obj, arg1;
{
	struct quaddata *qdata;
	GetQUAD(arg1, qdata);
	free_quad(qdata);
	CHECK_GLERROR	
	return Qnil;
}
static VALUE
glu_QuadricNormals(obj, arg1, arg2)
VALUE obj, arg1, arg2;
{
	struct quaddata* qdata;
	GLenum normals;
	GetQUAD(arg1, qdata);
	normals = (GLenum)NUM2INT(arg2);
	gluQuadricNormals(qdata->qobj, normals);
	CHECK_GLERROR	
	return Qnil;
}
static VALUE
glu_QuadricTexture(obj, arg1, arg2)
VALUE obj, arg1, arg2;
{
	struct quaddata* qdata;
	GLboolean textureCoords;
	GetQUAD(arg1, qdata);
	textureCoords = (GLboolean)NUM2INT(arg2);
	gluQuadricTexture(qdata->qobj, textureCoords);
	CHECK_GLERROR	
	return Qnil;
}
static VALUE
glu_QuadricOrientation(obj, arg1, arg2)
VALUE obj, arg1, arg2;
{
	struct quaddata* qdata;
	GLenum orientation;
	GetQUAD(arg1, qdata);
	orientation = (GLenum)NUM2INT(arg2);
	gluQuadricOrientation(qdata->qobj, orientation);
	CHECK_GLERROR	
	return Qnil;
}
static VALUE
glu_QuadricDrawStyle(obj, arg1, arg2)
VALUE obj, arg1, arg2;
{
	struct quaddata* qdata;
	GLenum drawStyle;
	GetQUAD(arg1, qdata);
	drawStyle = (GLenum)NUM2INT(arg2);
	gluQuadricDrawStyle(qdata->qobj, drawStyle);
	CHECK_GLERROR	
	return Qnil;
}
static VALUE
glu_Cylinder(obj, arg1, arg2, arg3, arg4, arg5, arg6)
VALUE obj, arg1, arg2, arg3, arg4, arg5, arg6;
{
	struct quaddata* qdata;
	GLdouble baseRadius;
	GLdouble topRadius;
	GLdouble height;
	GLint slices;
	GLint stacks;

	GetQUAD(arg1, qdata);
	baseRadius = (GLdouble)NUM2DBL(arg2);
	topRadius = (GLdouble)NUM2DBL(arg3);
	height = (GLdouble)NUM2DBL(arg4);
	slices = (GLint)NUM2INT(arg5);
	stacks = (GLint)NUM2INT(arg6);

	rb_ary_push(q_current, arg1);
	gluCylinder(qdata->qobj, baseRadius, topRadius, height, slices, stacks);
	rb_ary_pop(q_current);
	CHECK_GLERROR	
	return Qnil;
}
static VALUE
glu_Disk(obj, arg1, arg2, arg3, arg4, arg5)
VALUE obj, arg1, arg2, arg3, arg4, arg5;
{
	struct quaddata* qdata;
	GLdouble innerRadius;
	GLdouble outerRadius;
	GLint slices;
	GLint loops;
	
	GetQUAD(arg1, qdata);
	innerRadius = (GLdouble)NUM2DBL(arg2);
	outerRadius = (GLdouble)NUM2DBL(arg3);
	slices = (GLint)NUM2INT(arg4);
	loops = (GLint)NUM2INT(arg5);

	rb_ary_push(q_current, arg1);

	gluDisk(qdata->qobj, innerRadius, outerRadius, slices, loops);
	rb_ary_pop(q_current);
	CHECK_GLERROR	
	return Qnil;
}
static VALUE
glu_PartialDisk(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7)
VALUE obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7;
{
	struct quaddata* qdata;
	GLdouble innerRadius;
	GLdouble outerRadius;
	GLint slices;
	GLint loops;
	GLdouble startAngle;
	GLdouble sweepAngle;
	
	GetQUAD(arg1, qdata);
	innerRadius = (GLdouble)NUM2DBL(arg2);
	outerRadius = (GLdouble)NUM2DBL(arg3);
	slices = (GLint)NUM2INT(arg4);
	loops = (GLint)NUM2INT(arg5);
	startAngle = (GLdouble)NUM2DBL(arg6);
	sweepAngle = (GLdouble)NUM2DBL(arg7);

	rb_ary_push(q_current, arg1);
	gluPartialDisk(qdata->qobj, innerRadius, outerRadius, slices, loops, startAngle, sweepAngle);
	rb_ary_pop(q_current);
	CHECK_GLERROR	
	return Qnil;
}
static VALUE
glu_Sphere(obj, arg1, arg2, arg3, arg4)
VALUE obj, arg1, arg2, arg3, arg4;
{
	struct quaddata* qdata;
	GLdouble radius;
	GLint slices;
	GLint stacks;

	GetQUAD(arg1, qdata);
	radius = (GLdouble)NUM2DBL(arg2);
	slices = (GLint)NUM2INT(arg3);
	stacks = (GLint)NUM2INT(arg4);

	rb_ary_push(q_current, arg1);
	gluSphere(qdata->qobj, radius, slices, stacks);
	rb_ary_pop(q_current);
	CHECK_GLERROR	
	return Qnil;
}

/* */

static VALUE
glu_LookAt(obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
{
	GLdouble eyex;
	GLdouble eyey;
	GLdouble eyez;
	GLdouble centerx;
	GLdouble centery;
	GLdouble centerz;
	GLdouble upx;
	GLdouble upy;
	GLdouble upz;
	eyex = (GLdouble)NUM2DBL(arg1);
	eyey = (GLdouble)NUM2DBL(arg2);
	eyez = (GLdouble)NUM2DBL(arg3);
	centerx = (GLdouble)NUM2DBL(arg4);
	centery = (GLdouble)NUM2DBL(arg5);
	centerz = (GLdouble)NUM2DBL(arg6);
	upx = (GLdouble)NUM2DBL(arg7);
	upy = (GLdouble)NUM2DBL(arg8);
	upz = (GLdouble)NUM2DBL(arg9);
	gluLookAt( eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz );
	CHECK_GLERROR	
	return Qnil;
}
static VALUE
glu_Ortho2D(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
	GLdouble left;
	GLdouble right;
	GLdouble bottom;
	GLdouble top;
	left = (GLdouble)NUM2DBL(arg1);
	right = (GLdouble)NUM2DBL(arg2);
	bottom = (GLdouble)NUM2DBL(arg3);
	top = (GLdouble)NUM2DBL(arg4);
	gluOrtho2D(left,right,bottom,top);
	CHECK_GLERROR	
	return Qnil;
}
static VALUE
glu_Perspective(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
	GLdouble fovy;
	GLdouble aspect;
	GLdouble zNear;
	GLdouble zFar;
	fovy = (GLdouble)NUM2DBL(arg1);
	aspect = (GLdouble)NUM2DBL(arg2);
	zNear = (GLdouble)NUM2DBL(arg3);
	zFar = (GLdouble)NUM2DBL(arg4);
	gluPerspective(fovy,aspect,zNear,zFar);
	CHECK_GLERROR	
	return Qnil;
}
static VALUE
glu_PickMatrix(argc,argv,obj)
int argc;
VALUE* argv;
VALUE obj;
{
	GLdouble x;
	GLdouble y;
	GLdouble width;
	GLdouble height;
	GLint viewport[4];
	
	VALUE args[5];
	
	switch (rb_scan_args(argc, argv, "23", &args[0], &args[1], &args[2], &args[3], &args[4])) {
		case 2:
			width = 5.0f;
			height = 5.0f;
			glGetIntegerv(GL_VIEWPORT, viewport);
			break;
		case 4:
			width = (GLdouble)NUM2DBL(args[2]);
			height = (GLdouble)NUM2DBL(args[3]);
			glGetIntegerv(GL_VIEWPORT, viewport);
			break;
		case 5:
			width = (GLdouble)NUM2DBL(args[2]);
			height = (GLdouble)NUM2DBL(args[3]);
			ary2cint(args[4], viewport, 4);
			break;
		default:
			rb_raise(rb_eArgError, "gluPickMatrix needs 2,4 or 5 parameters");
	}
	x = (GLdouble)NUM2DBL(args[0]);
	y = (GLdouble)NUM2DBL(args[1]);
	gluPickMatrix(x, y, width, height, viewport);
	CHECK_GLERROR	
	return Qnil;
}

static VALUE
glu_Project(argc,argv,obj)
int argc;
VALUE* argv;
VALUE obj;
{
	GLdouble ox;
	GLdouble oy;
	GLdouble oz;
	GLdouble mdl_mtx[4*4];
	GLdouble prj_mtx[4*4];
	GLint vport[4];
	GLdouble wx;
	GLdouble wy;
	GLdouble wz;

	VALUE args[6];
	
	switch (rb_scan_args(argc, argv, "33", &args[0], &args[1], &args[2], &args[3], &args[4], &args[5])) {
		case 3:
			glGetDoublev(GL_MODELVIEW_MATRIX, mdl_mtx);
			glGetDoublev(GL_PROJECTION_MATRIX, prj_mtx);
			glGetIntegerv(GL_VIEWPORT, vport);
			break;
		case 6:
			ary2cmatdouble(args[3], mdl_mtx, 4, 4);
			ary2cmatdouble(args[4], prj_mtx, 4, 4);
			ary2cint(args[5], vport, 4);
			break;
		default:
			rb_raise(rb_eArgError, "gluProject needs 3 or 6 parameters");
	}
	ox = (GLdouble)NUM2DBL(args[0]);
	oy = (GLdouble)NUM2DBL(args[1]);
	oz = (GLdouble)NUM2DBL(args[2]);
	
	if (gluProject(ox, oy, oz, mdl_mtx, prj_mtx, vport, &wx, &wy, &wz) == GL_TRUE) {
		CHECK_GLERROR	
		return rb_ary_new3(3, rb_float_new(wx), rb_float_new(wy), rb_float_new(wz));
	} else {
		CHECK_GLERROR	
		check_for_gluerror(GLU_INVALID_VALUE);
		return Qnil; /* not reached */
	}
}
static VALUE
glu_UnProject(argc,argv,obj)
int argc;
VALUE* argv;
VALUE obj;
{
	GLdouble wx;
	GLdouble wy;
	GLdouble wz;
	GLdouble mdl_mtx[4*4];
	GLdouble prj_mtx[4*4];
	GLint vport[4];
	GLdouble ox;
	GLdouble oy;
	GLdouble oz;
	
	VALUE args[6];
	
	switch (rb_scan_args(argc, argv, "33", &args[0], &args[1], &args[2], &args[3], &args[4], &args[5])) {
		case 3:
			glGetDoublev(GL_MODELVIEW_MATRIX, mdl_mtx);
			glGetDoublev(GL_PROJECTION_MATRIX, prj_mtx);
			glGetIntegerv(GL_VIEWPORT, vport);
			break;
		case 6:
			ary2cmatdouble(args[3], mdl_mtx, 4, 4);
			ary2cmatdouble(args[4], prj_mtx, 4, 4);
			ary2cint(args[5], vport, 4);
			break;
		default:
			rb_raise(rb_eArgError, "gluUnProject needs 3 or 6 parameters");
	}
	wx = (GLdouble)NUM2DBL(args[0]);
	wy = (GLdouble)NUM2DBL(args[1]);
	wz = (GLdouble)NUM2DBL(args[2]);
	
	if (gluUnProject(wx, wy, wz, mdl_mtx, prj_mtx, vport, &ox, &oy, &oz) == GL_TRUE) {
		CHECK_GLERROR	
		return rb_ary_new3(3, rb_float_new(ox), rb_float_new(oy), rb_float_new(oz));
	} else {
		CHECK_GLERROR	
		check_for_gluerror(GLU_INVALID_VALUE);
		return Qnil; /* not reached */
	}
}

static VALUE
glu_Build1DMipmaps(obj, arg1, arg2, arg3, arg4, arg5, arg6)
VALUE obj, arg1, arg2, arg3, arg4, arg5, arg6;
{
	GLenum target;
	GLint components;
	GLint width;
	GLenum format;
	GLenum type;
	int ret;
	
	target = (GLenum)NUM2INT(arg1);
	components = (GLint)NUM2INT(arg2);
	width = (GLint)NUM2INT(arg3);
	format = (GLenum)NUM2INT(arg4);
	type = (GLenum)NUM2INT(arg5);
	Check_Type(arg6,T_STRING);
	CheckDataSize(type,format,width,arg6);

	ret = gluBuild1DMipmaps(target, components, width, format, type, RSTRING_PTR(arg6));
	check_for_gluerror(ret);
	CHECK_GLERROR	
	return INT2NUM(ret);
}

static VALUE
glu_Build2DMipmaps(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7)
VALUE obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7;
{
	GLenum target;
	GLint components;
	GLint width;
	GLint height;
	GLenum format;
	GLenum type;
	int ret;
	
	target = (GLenum)NUM2INT(arg1);
	components = (GLint)NUM2INT(arg2);
	width = (GLint)NUM2INT(arg3);
	height = (GLint)NUM2INT(arg4);
	format = (GLenum)NUM2INT(arg5);
	type = (GLenum)NUM2INT(arg6);
	Check_Type(arg7,T_STRING);
	CheckDataSize(type,format,width*height,arg7);

	ret = gluBuild2DMipmaps(target, components, width, height, format, type, RSTRING_PTR(arg7));
	check_for_gluerror(ret);
	CHECK_GLERROR	
	return INT2NUM(ret);
}

static VALUE
glu_ScaleImage(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)
VALUE obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8;
{
	GLenum format;
	GLint widthin;
	GLint heightin;
	GLenum typein;
	void* datain;
	GLint widthout;
	GLint heightout;
	GLenum typeout;
	VALUE ret;
	GLint retcode;
	
	format = (GLenum)NUM2INT(arg1);
	widthin = (GLint)NUM2INT(arg2);
	heightin = (GLint)NUM2INT(arg3);
	typein = (GLenum)NUM2INT(arg4);
	Check_Type(arg5,T_STRING);
	CheckDataSize(typein,format,heightin*widthin,arg5);
	datain = RSTRING_PTR(arg5);
	widthout = (GLint)NUM2INT(arg6);
	heightout = (GLint)NUM2INT(arg7);
	typeout = (GLenum)NUM2INT(arg8);
	ret = allocate_buffer_with_string(GetDataSize(typeout,format,widthout*heightout));
	retcode = gluScaleImage(format, widthin, heightin, typein, datain,
		widthout, heightout, typeout, (GLvoid*)RSTRING_PTR(ret));

	check_for_gluerror(retcode);
	CHECK_GLERROR	
	return ret;
}

static VALUE
glu_ErrorString(obj, arg1)
VALUE obj, arg1;
{
	GLenum errorCode;
	GLubyte* error;
	errorCode = (GLenum)NUM2INT(arg1);
	error = (GLubyte*)gluErrorString(errorCode);
	CHECK_GLERROR	
	if (error)
		return rb_str_new2((char *)error);
	else
		return Qnil;
}
static VALUE
glu_GetString(obj, arg1)
VALUE obj, arg1;
{
	GLenum name;
	GLubyte* str;
	name = (GLenum)NUM2INT(arg1);
	str = (GLubyte*)gluGetString(name);
	CHECK_GLERROR	
	if (str)
		return rb_str_new2((char *)str);
	else
		return Qnil;
}

static VALUE module;

DLLEXPORT void Init_glu()
{
	callId = rb_intern("call");
	refId = rb_intern("[]");
	module = rb_define_module("Glu");

	glu_init_enums(module);
	
	rb_define_module_function(module, "gluNewNurbsRenderer", glu_NewNurbsRenderer, 0);
	rb_define_module_function(module, "gluDeleteNurbsRenderer", glu_DeleteNurbsRenderer, 1);
	rb_define_module_function(module, "gluNurbsProperty", glu_NurbsProperty, 3);
	rb_define_module_function(module, "gluGetNurbsProperty", glu_GetNurbsProperty, 2);
	rb_define_module_function(module, "gluBeginCurve", glu_BeginCurve, 1);
	rb_define_module_function(module, "gluEndCurve", glu_EndCurve, 1);
	rb_define_module_function(module, "gluNurbsCurve", glu_NurbsCurve, -1);
	rb_define_module_function(module, "gluBeginSurface", glu_BeginSurface, 1);
	rb_define_module_function(module, "gluEndSurface", glu_EndSurface, 1);
	rb_define_module_function(module, "gluNurbsSurface", glu_NurbsSurface, -1);
	rb_define_module_function(module, "gluBeginTrim", glu_BeginTrim, 1);
	rb_define_module_function(module, "gluEndTrim", glu_EndTrim, 1);
	rb_define_module_function(module, "gluPwlCurve", glu_PwlCurve, -1);
	rb_define_module_function(module, "gluNewTess", glu_NewTess, 0);
	rb_define_module_function(module, "gluDeleteTess", glu_DeleteTess, 1);
	rb_define_module_function(module, "gluTessCallback", glu_TessCallback, 3);
	rb_define_module_function(module, "gluBeginPolygon", glu_BeginPolygon, 1);
	rb_define_module_function(module, "gluTessVertex", glu_TessVertex, 3);
	rb_define_module_function(module, "gluNextContour", glu_NextContour, 2);
	rb_define_module_function(module, "gluEndPolygon", glu_EndPolygon, 1);
	rb_define_module_function(module, "gluTessBeginPolygon", glu_TessBeginPolygon, 2);
	rb_define_module_function(module, "gluTessBeginContour",  glu_TessBeginContour, 1);
	rb_define_module_function(module, "gluTessEndContour", glu_TessEndContour, 1);
	rb_define_module_function(module, "gluTessEndPolygon", glu_TessEndPolygon, 1);
	rb_define_module_function(module, "gluTessProperty", glu_TessProperty, 3);
	rb_define_module_function(module, "gluTessNormal", glu_TessNormal, 4);
	rb_define_module_function(module, "gluGetTessProperty", glu_GetTessProperty, 2);
	rb_define_module_function(module, "gluNewQuadric", glu_NewQuadric, 0);
	rb_define_module_function(module, "gluDeleteQuadric", glu_DeleteQuadric, 1);
	rb_define_module_function(module, "gluQuadricNormals", glu_QuadricNormals, 2);
	rb_define_module_function(module, "gluQuadricTexture", glu_QuadricTexture, 2);
	rb_define_module_function(module, "gluQuadricOrientation", glu_QuadricOrientation, 2);
	rb_define_module_function(module, "gluQuadricDrawStyle", glu_QuadricDrawStyle, 2);
	rb_define_module_function(module, "gluCylinder", glu_Cylinder, 6);
	rb_define_module_function(module, "gluDisk", glu_Disk, 5);
	rb_define_module_function(module, "gluPartialDisk", glu_PartialDisk, 7);
	rb_define_module_function(module, "gluSphere", glu_Sphere, 4);
	
	rb_define_module_function(module, "gluLookAt", glu_LookAt, 9);
	rb_define_module_function(module, "gluOrtho2D", glu_Ortho2D, 4);
	rb_define_module_function(module, "gluPerspective", glu_Perspective, 4);
	rb_define_module_function(module, "gluPickMatrix", glu_PickMatrix, -1);
	rb_define_module_function(module, "gluProject", glu_Project, -1);
	rb_define_module_function(module, "gluUnProject", glu_UnProject, -1);
	rb_define_module_function(module, "gluBuild1DMipmaps", glu_Build1DMipmaps, 6);
	rb_define_module_function(module, "gluBuild2DMipmaps", glu_Build2DMipmaps, 7);
	rb_define_module_function(module, "gluScaleImage", glu_ScaleImage, 8);
	rb_define_module_function(module, "gluErrorString", glu_ErrorString, 1);
	rb_define_module_function(module, "gluGetString", glu_GetString, 1);
	
	rb_define_module_function(module, "gluLoadSamplingMatrices",glu_LoadSamplingMatrices,4);
	rb_define_module_function(module, "gluQuadricCallback", glu_QuadricCallback, 3);
	rb_define_module_function(module, "gluNurbsCallback", glu_NurbsCallback, 3);

	Class_GLUError = rb_define_class_under(module, "Error", rb_eStandardError);

	rb_define_method(Class_GLUError, "initialize", GLUError_initialize, 2);
	rb_define_attr(Class_GLUError, "id", 1, 0);

	cNurbs = rb_define_class("Nurbs", rb_cObject);
	cTess = rb_define_class("Tess", rb_cObject);
	cQuad = rb_define_class("Quadric", rb_cObject);
	
	rb_global_variable(&t_current); /* current active tesselator, nurbs and quadric, used for callbacks */
	t_current = rb_ary_new();
	rb_global_variable(&n_current); 
	n_current = rb_ary_new();
	rb_global_variable(&q_current); 
	q_current = rb_ary_new();
}
