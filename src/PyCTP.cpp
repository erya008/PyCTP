// PyCTP.cpp : Defines the exported functions for the DLL application.
//

// CTP ת python
// ��Ҫ���� CTP ���dll�ļ�
// beta δȷ���ȶ�
//cpp�ӿ�ctp, ƽ������pyctp
//#author: ʯ׿��
//#http://www.shizhuolin.com
//#mailto:shizhuolin@hotmail.com

#include "stdafx.h"
#include "UserApiDataType.h"
#include "MdApi.h"
#include "TraderApi.h"

#define MODULE_NAME "PyCTP"
#define MODULE_DOC "CTP 201612191535 for Python author:http://www.shizhuolin.com shizhuolin@hotmail.com qq:383193853"

//����ģ��
#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef PyCTP_Module = {PyModuleDef_HEAD_INIT, MODULE_NAME, MODULE_DOC, -1};
#endif

//��ʼ��ģ��
PyMODINIT_FUNC
#if PY_MAJOR_VERSION >= 3
	PyInit_PyCTP(void)
#else
	initPyCTP(void)
#endif
{
	/* ����չ���߳� */
	PyEval_InitThreads();

#if PY_MAJOR_VERSION >= 3 
	PyObject *m = PyModule_Create(&PyCTP_Module);
#else
	static PyMethodDef PyCTPMethods[] = {{NULL, NULL, 0, NULL}};
	PyObject *m = Py_InitModule3(MODULE_NAME, PyCTPMethods, MODULE_DOC);
#endif
	if( m == nullptr )
	{
		PyErr_SetString(PyExc_RuntimeError, "failed to create module.");
#if PY_MAJOR_VERSION >= 3 
		return nullptr;
#else
		return;
#endif
	}

	/* ׼���ö���ʹ�� CThostFtdcMdApi  */
	if (PyType_Ready(&CTP_THOST_FTDC_MD_API_TYPE) < 0){
		PyErr_SetString(PyExc_RuntimeError, "can't initialize PyCTP.CThostFtdcMdApi");
#if PY_MAJOR_VERSION >= 3 
		return nullptr;
#else
		return;
#endif
	}

	Py_INCREF(&CTP_THOST_FTDC_MD_API_TYPE);
	PyModule_AddObject(m, "CThostFtdcMdApi", (PyObject *)&CTP_THOST_FTDC_MD_API_TYPE);

	/* ׼���ö���ʹ�� CThostFtdcTraderApi  */
	if (PyType_Ready(&CTP_THOST_FTDC_TRADER_API_TYPE) < 0){
		PyErr_SetString(PyExc_RuntimeError, "can't initialize PyCTP.CThostFtdcTraderApi");
#if PY_MAJOR_VERSION >= 3 
		return nullptr;
#else
		return;
#endif
	}

	Py_INCREF(&CTP_THOST_FTDC_TRADER_API_TYPE);
	PyModule_AddObject(m, "CThostFtdcTraderApi", (PyObject *)&CTP_THOST_FTDC_TRADER_API_TYPE);

	//��������CTPԤ���峣��
	PyModule_AddCTPConstant(m);

#if PY_MAJOR_VERSION >= 3 
	return m;
#endif
};
