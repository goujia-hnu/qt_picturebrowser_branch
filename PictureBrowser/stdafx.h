#include <QtWidgets>

#ifdef DEBUG
#define NDEBUG //#����assert����
#endif
#include <assert.h>

#define TitleBar_BackGround QColor(70, 124, 212)		//������������ɫ
#define ToolButton_HoverColor QColor(94,172,255)		//ToolButton���hover��ɫ
#define ToolButton_PressedColor QColor(63,111,190)		//ToolButton���ʱ��ɫ
#define Button_Height dpiScaled(30)        // ��ť�߶�
#define Button_Width dpiScaled(40)         // ��ť���
#define Title_Height dpiScaled(30)         // �������߶�

typedef float REAL;

void getDpi(IN REAL* pDpix, IN REAL* pDpiy);
qreal dpiScaled(const qreal value);
