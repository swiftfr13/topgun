#include <conio.h>
#include <time.h>
#define IMGSIZE 193//캐릭터 이미지의 크기
#define WIDTH 1920//배경화면의 X 크기
#define HEIGHT 1080//배경화면의 Y 크기
#define pi 3.14159265358979323
extern int p1x, p2x, p1y, p2y, r1, r2;
void GetBMP();
void movep(int p1spd, int p2spd, int p1tr, int p2tr)//플레이어 캐릭터의 회전 값을 증가/감소시키는 함수
{
	if (GetAsyncKeyState(0x53) & 0x0001)//S가 눌릴 시 플레이어 1의 회전값을 추가하고, 16으로 나눈 나머지를 구한다
	{
		r1++;
		r1 %= 16;
	}
	if (GetAsyncKeyState(0x57) & 0x0001)//W가 눌릴 시 플레이어 1의 회전값을 감소시키고, 0 이하로 내려가면 16만큼 더해준다
	{
		r1--;
		if (r1 < 0)
			r1 += 16;
		r1 %= 16;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x0001)//화살표 위가 눌릴 시 플레이어 2의 회전값을 추가하고, 16으로 나눈 나머지를 구한다
	{
		r2++;
		r2 %= 16;
	}
	if (GetAsyncKeyState(VK_UP) & 0x0001)//화살표 아래가 눌릴 시 플레이어 2의 회전값을 감소시키고, 0 이하로 내려가면 16만큼 더해준다
	{
		r2--;
		if (r2 < 0)
			r2 += 16;
		r2 %= 16;
	}
	p1x += cos(r1 * 22.5 * pi / 180) * p1spd;//플레이어의 회전 값에 따라 캐릭터를 움직인다(math.h 활용)
	p1y -= sin(r1 * 22.5 * pi / 180) * p1spd;
	p2x += cos(r2 * 22.5 * pi / 180) * p2spd;
	p2y += sin(r2 * 22.5 * pi / 180) * p2spd;
}
void death(HWND hWnd, int dpi, HBITMAP image, int* p1h, int* p2h, int count)//플레이어가 죽을 시 폭발 이미지를 출력한다
{
	HDC hdc = GetDC(hWnd);
	HDC memdc = CreateCompatibleDC(hdc);
	HBITMAP bitmap = CreateCompatibleBitmap(hdc, IMGSIZE * 6, IMGSIZE);
	SelectObject(memdc, bitmap);
	GetBMP(hdc, memdc, image);
	if (*p1h <= 0)//플레이어 1이 죽을 시 플레이어 1의 좌표에 폭발 이미지를 출력한다
		for (int i = 0; i < 7; i++)
		{
			TransparentBlt(hdc, p1x, p1y, IMGSIZE, IMGSIZE, memdc, IMGSIZE * i, 0, IMGSIZE, IMGSIZE, RGB(255, 255, 255));
			Sleep(150);
			if (count == 1)
				goto next;
		}
next:
	if (*p2h <= 0)//플레이어 2가 죽을 시 플레이어 1의 좌표에 폭발 이미지를 출력한다
		for (int i = 0; i < 7; i++)
		{
			TransparentBlt(hdc, p2x, p2y, IMGSIZE, IMGSIZE, memdc, IMGSIZE * i, 0, IMGSIZE, IMGSIZE, RGB(255, 255, 255));
			Sleep(150);
			if (count == 1)
				goto next2;
		}
next2:
	DeleteDC(memdc);
	DeleteObject(bitmap);
	ReleaseDC(hWnd, hdc);
}
void fallout(int* p1h, int* p2h)
{
	if (p1y <= -97 || HEIGHT - 97 <= p1y || p1x < -97 || WIDTH - 97 < p1x)//플레이어의 위치가 화면 밖으로 이동하면 해당 플레이어의 체력을 0으로 바꾼다
		*p1h = 0;
	if (p2y + 97 <= 0 || HEIGHT - 97 <= p2y || p2x < -97 || WIDTH - 97 < p2x)
		*p2h = 0;
}