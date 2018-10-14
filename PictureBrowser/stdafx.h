#include <QtWidgets>

#ifdef DEBUG
#define NDEBUG //#禁用assert调用
#endif
#include <assert.h>

#define TitleBar_BackGround QColor(70, 124, 212)		//标题栏背景颜色
#define ToolButton_HoverColor QColor(94,172,255)		//ToolButton鼠标hover颜色
#define ToolButton_PressedColor QColor(63,111,190)		//ToolButton点击时颜色
#define Button_Height dpiScaled(30)        // 按钮高度
#define Button_Width dpiScaled(40)         // 按钮宽度
#define Title_Height dpiScaled(30)         // 标题栏高度

typedef float REAL;

void getDpi(IN REAL* pDpix, IN REAL* pDpiy);
qreal dpiScaled(const qreal value);
