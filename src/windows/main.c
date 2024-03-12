#include "../../kalos.h"
#ifdef _WIN32

#include <windows.h>
#include <tchar.h>

HWND kalos_window;
HDC kalos_device_context;
HBITMAP kalos_buffer;
int kalos_width = 400;
int kalos_height = 400;

int kalos_init() {
    WNDCLASS window_class = { 0 };
    window_class.lpfnWndProc = DefWindowProc;
    window_class.hInstance = GetModuleHandle(NULL);
    window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    window_class.lpszClassName = _T("KalosWindowClass");

    if (!RegisterClass(&window_class)) {
        return KALOS_INIT_FAIL;
    }

    kalos_window = CreateWindow(
        _T("KalosWindowClass"), _T("Kalos Window"),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        kalos_width, kalos_height, NULL, NULL,
        GetModuleHandle(NULL), NULL
    );

    if (!kalos_window) {
        return KALOS_INIT_FAIL;
    }

    kalos_device_context = GetDC(kalos_window);

    BITMAPINFO bitmap_info = { 0 };
    bitmap_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmap_info.bmiHeader.biWidth = kalos_width;
    bitmap_info.bmiHeader.biHeight = -kalos_height; // Negative height to ensure top-down DIB
    bitmap_info.bmiHeader.biPlanes = 1;
    bitmap_info.bmiHeader.biBitCount = 32;
    kalos_buffer = CreateDIBSection(kalos_device_context, &bitmap_info, DIB_RGB_COLORS, NULL, NULL, 0);

    if (!kalos_buffer) {
        return KALOS_INIT_FAIL;
    }

    SelectObject(kalos_device_context, kalos_buffer);

    return KALOS_INIT_SUCCESS;
}

void kalos_show_window() {
    ShowWindow(kalos_window, SW_SHOWDEFAULT);
    UpdateWindow(kalos_window);
}

void kalos_update_window() {
    HDC window_dc = GetDC(kalos_window);
    BitBlt(window_dc, 0, 0, kalos_width, kalos_height, kalos_device_context, 0, 0, SRCCOPY);
    ReleaseDC(kalos_window, window_dc);
}

void kalos_set_pixel(int x, int y, unsigned char r, unsigned char g, unsigned char b) {
    SetPixel(kalos_device_context, x, y, RGB(r, g, b));
}

void kalos_fill_window(unsigned char r, unsigned char g, unsigned char b) {
    HBRUSH brush = CreateSolidBrush(RGB(r, g, b));
    RECT rect = { 0, 0, kalos_width, kalos_height };
    FillRect(kalos_device_context, &rect, brush);
    DeleteObject(brush);
}

void kalos_fill_rect(int x, int y, int h, int w, unsigned char r, unsigned char g, unsigned char b) {
    HBRUSH brush = CreateSolidBrush(RGB(r, g, b));
    RECT rect = { x, y, x + w, y + h };
    FillRect(kalos_device_context, &rect, brush);
    DeleteObject(brush);
}

void kalos_draw_line(int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b) {
    HPEN pen = CreatePen(PS_SOLID, 1, RGB(r, g, b));
    SelectObject(kalos_device_context, pen);
    MoveToEx(kalos_device_context, x1, y1, NULL);
    LineTo(kalos_device_context, x2, y2);
    DeleteObject(pen);
}

void kalos_draw_disk(int x, int y, int radius, unsigned char r, unsigned char g, unsigned char b) {
    HBRUSH brush = CreateSolidBrush(RGB(r, g, b));
    Ellipse(kalos_device_context, x - radius, y - radius, x + radius, y + radius);
    DeleteObject(brush);
}

void kalos_draw_circle(int x, int y, int radius, unsigned char r, unsigned char g, unsigned char b) {
    HBRUSH brush = CreateSolidBrush(RGB(r, g, b));
    Ellipse(kalos_device_context, x - radius, y - radius, x + radius, y + radius);
    DeleteObject(brush);
}

void __kalos_handle_window_resize(int new_width, int new_height) {
    kalos_width = new_width;
    kalos_height = new_height;

    DeleteObject(kalos_buffer);
    BITMAPINFO bitmap_info = { 0 };
    bitmap_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmap_info.bmiHeader.biWidth = kalos_width;
    bitmap_info.bmiHeader.biHeight = -kalos_height;
    bitmap_info.bmiHeader.biPlanes = 1;
    bitmap_info.bmiHeader.biBitCount = 32;
    kalos_buffer = CreateDIBSection(kalos_device_context, &bitmap_info, DIB_RGB_COLORS, NULL, NULL, 0);

    SelectObject(kalos_device_context, kalos_buffer);
}

int kalos_get_height() {
    return kalos_height;
}

int kalos_get_width() {
    return kalos_width;
}

// Windows doesn't handle events in the same way as Xlib, so this part will be different.

void kalos_free_events(kalos_event_t *events) {
    free(events);
}

int event_len(kalos_event_t *events) {
    int i = 0;
    for (i = 0; events[i].is_pressed != 2; i++);
    return i;
}

void kalos_end() {
    DeleteObject(kalos_buffer);
    ReleaseDC(kalos_window, kalos_device_context);
    DestroyWindow(kalos_window);
}



void kalos_sleep_ms(long long int x) {
    return;
}

kalos_event_t *kalos_get_events() {
    kalos_event_t *e = malloc(sizeof(kalos_event_t));
    e[0].is_pressed = 2;
    return e;
}



#endif
