package window32;

/*
 * To change this template, choose Tools | Templates and open the template in
 * the editor.
 */
/**
 *
 * @author stark
 */
/*
 * HWND WINAPI FindWindow( __in_opt LPCTSTR lpClassName, __in_opt LPCTSTR
 * lpWindowName );
 *
 * HWND WINAPI FindWindowEx( __in_opt HWND hwndParent, __in_opt HWND
 * hwndChildAfter, __in_opt LPCTSTR lpszClass, __in_opt LPCTSTR lpszWindow );
 *
 * LRESULT WINAPI SendMessage( __in HWND hWnd, __in UINT Msg, __in WPARAM
 * wParam, __in LPARAM lParam );
 */
/*
 * public native int FindWindow(String cName, String wName); funtion return
 * handle value if window found else 0; public native int FindWindowEx(int pHNW,
 * int cHNW, String cName, String wName); funtion return handle value if window
 * found else 0; public native void SendMessage(int HNW, int MSG, int wP, String
 * lP); sendmessege to window , this funtion always use WM_SETTEXT (what ever
 * int value you put)and returns nothing; public native String SendMessage(int
 * HNW, int MSG, int wP, int sZ); sendmessege to window , this funtion always
 * use WM_GETTEXT (what ever int value you put)and returns value from window;
 * platform - windows xp 32bit c/c++ compiled - with Pelles C for Windows -
 * Version 7.00.347 Release Candidate #3 java compiled - with java jdk1.6.0_25
 */
/*
 * ex : public static void main(String[] args) { Window32 w32o = new Window32();
 * int hv = w32o.FindWindow("SciCalc", "Calculator"); System.out.println("" +
 * hv); int hvc = w32o.FindWindowEx(hv, 0, "Edit", "NULL");
 * System.out.println("" + hvc); w32o.SendMessage(hvc, 0, 0, "555"); String gtv
 * = w32o.SendMessage(0, 0, 999, 1000); System.out.println("" + gtv);
 *
 *
 * }
 */
public class Window32 {

    private static Window32 instence = null;

    public Window32() {
    }

    public static synchronized Window32 getInstence() {
        if (instence == null) {
            instence = new Window32();
        }
        return instence;
    }

    /**
     * @param args the command line arguments
     */
    public native int FindWindow(String cName, String wName);

    public native int FindWindowEx(int pHNW, int cHNW, String cName, String wName);

    public native void SendMessage(int HNW, int MSG, int wP, String lP);

    public native String SendMessage(int HNW, int MSG, int wP, int sZ);

    static {
        System.load(System.getProperty("user.dir") + System.getProperty("file.separator") + "window32.dll");
    }
}
