/****************************************************************************
 *                                                                          *
 * File    : dllmain.c                                                      *
 *                                                                          *
 * Purpose : Generic Win32 Dynamic Link Library (DLL).                      *
 *                                                                          *
 * History : Date      Reason                                               *
 *           00/00/00  Created                                              *
 *                                                                          *
 ****************************************************************************/

#define WIN32_LEAN_AND_MEAN  /* speed up */
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <tchar.h>

/*
 * Include our "interface" file and define a symbol
 * to indicate that we are *building* the DLL.
 */
#define _WINDOW32_
#include "WINDOW32.h"

/****************************************************************************
 *                                                                          *
 * Function: DllMain                                                        *
 *                                                                          *
 * Purpose : DLL entry and exit procedure.                                  *
 *                                                                          *
 * History : Date      Reason                                               *
 *           00/00/00  Created                                              *
 *                                                                          *
 ****************************************************************************/

BOOL APIENTRY DllMain(HINSTANCE hInstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            /*
             * Microsoft says:
             *
             * The DLL is being loaded into the virtual address space of the current
             * process as a result of the process starting up or as a result of a call
             * to LoadLibrary. DLLs can use this opportunity to initialize any instance
             * data or to use the TlsAlloc function to allocate a thread local storage
             * (TLS) index.
             */
            break;

        case DLL_THREAD_ATTACH:
            /*
             * Microsoft says:
             *
             * The current process is creating a new thread. When this occurs, the system
             * calls the entry-point function of all DLLs currently attached to the process.
             * The call is made in the context of the new thread. DLLs can use this opportunity
             * to initialize a TLS slot for the thread. A thread calling the DLL entry-point
             * function with DLL_PROCESS_ATTACH does not call the DLL entry-point function
             * with DLL_THREAD_ATTACH.
             *
             * Note that a DLL's entry-point function is called with this value only by threads
             * created after the DLL is loaded by the process. When a DLL is loaded using
             * LoadLibrary, existing threads do not call the entry-point function of the newly
             * loaded DLL.
             */
            break;

        case DLL_THREAD_DETACH:
            /*
             * Microsoft says:
             *
             * A thread is exiting cleanly. If the DLL has stored a pointer to allocated memory
             * in a TLS slot, it should use this opportunity to free the memory. The system calls
             * the entry-point function of all currently loaded DLLs with this value. The call
             * is made in the context of the exiting thread.
             */
            break;

        case DLL_PROCESS_DETACH:
            /*
             * Microsoft says:
             *
             * The DLL is being unloaded from the virtual address space of the calling process as
             * a result of unsuccessfully loading the DLL, termination of the process, or a call
             * to FreeLibrary. The DLL can use this opportunity to call the TlsFree function to
             * free any TLS indices allocated by using TlsAlloc and to free any thread local data.
             *
             * Note that the thread that receives the DLL_PROCESS_DETACH notification is not
             * necessarily the same thread that received the DLL_PROCESS_ATTACH notification.
             */
            break;
    }

    /* Return success */
    return TRUE;
}
/*
 HWND WINAPI FindWindow(
 __in_opt  LPCTSTR lpClassName,
 __in_opt  LPCTSTR lpWindowName
 );



 HWND WINAPI FindWindowEx(
 __in_opt  HWND hwndParent,
 __in_opt  HWND hwndChildAfter,
 __in_opt  LPCTSTR lpszClass,
 __in_opt  LPCTSTR lpszWindow
 );


 LRESULT WINAPI SendMessage(
 __in  HWND hWnd,
 __in  UINT Msg,
 __in  WPARAM wParam,
 __in  LPARAM lParam
 );
  
 */
char* jstringToChar(JNIEnv* env, jstring str)
 {
int length = (*env)->GetStringLength( env, str);
 const jchar* jcstr = (*env)->GetStringChars( env, str, 0 );
 char* rtn = (char*)malloc( length * 2 + 1 );
 int size = 0;
 size = WideCharToMultiByte(
 CP_ACP,
 0,
 (LPCWSTR)
 jcstr,
 length,
 rtn,
 (length*2 +1 ),
 NULL,
 NULL
 );
 if ( size <= 0 ) return 0;
 (*env)->ReleaseStringChars( env, str, jcstr );
 rtn[ size ] = 0;
return rtn;
}

JNIEXPORT jint JNICALL Java_window32_Window32_FindWindow
  (JNIEnv *env, jobject obj,jstring jstrcn,jstring jstrwn){
   const char * cnstr =  jstringToChar(env,jstrcn);
   const char * wnstr =  jstringToChar(env,jstrwn);
   HWND hWindow = FindWindow(cnstr,wnstr);
return (int)hWindow;
}
JNIEXPORT jint JNICALL Java_window32_Window32_FindWindowEx
  (JNIEnv *env, jobject obj, jint phnw, jint chnw, jstring jstrcn, jstring jstrwn){
   const char * cnstr = (*env)->GetStringUTFChars(env, jstrcn, 0);
   const char * wnstr = (*env)->GetStringUTFChars(env, jstrwn, 0);
	LPCSTR js = NULL;
    if(strcmp ("NULL",wnstr) != 0){
	js = (LPCSTR)wnstr;
	}
   HWND hWindow = FindWindowEx((HWND)phnw,(HWND)chnw,cnstr,js);
   (*env)->ReleaseStringUTFChars(env, jstrcn, cnstr);
   (*env)->ReleaseStringUTFChars(env, jstrwn, wnstr);

return (int)hWindow;
}
JNIEXPORT void JNICALL Java_window32_Window32_SendMessage__IIILjava_lang_String_2
	(JNIEnv *env, jobject obj, jint hwnd, jint msg, jint wp, jstring lp){
    const char * lpstr = (*env)->GetStringUTFChars(env, lp, 0);
     SendMessage((HWND)hwnd,WM_SETTEXT,wp,(LPARAM)lpstr);
	(*env)->ReleaseStringUTFChars(env, lp, lpstr);
}

JNIEXPORT jstring JNICALL Java_window32_Window32_SendMessage__IIII
  (JNIEnv *env, jobject obj, jint hwnd, jint msg, jint wp, jint sz){
   jstring javaString;  
   char param[sz];
   SendMessage((HWND)hwnd,WM_GETTEXT,wp,(LPARAM)param);
   javaString = (jstring)(*env)->NewStringUTF(env, (const char *)param);
   return javaString;
}
