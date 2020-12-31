int displaystart(HWND hWnd, int dpi, HBITMAP image)//시작 화면을 보여주고, 게임 모드를 입력받는다
{
	int select = 0;
	HDC hdc = GetDC(hWnd);
	HDC memdc = CreateCompatibleDC(hdc);
	HBITMAP bitmap = CreateCompatibleBitmap(hdc, WIDTH * 5, HEIGHT);
	SelectObject(memdc, bitmap);
	GetBMP(hdc, memdc, image);
	while (1)
	{
		while (1)
		{
			clearcursor();//커서를 없애준다
			StretchBlt(hdc, 0, 0, WIDTH, HEIGHT, memdc, WIDTH * 3, 0, WIDTH, HEIGHT, SRCCOPY);//시작 화면 두 장을 번갈아가면서 보여준다
			Sleep(400);
			StretchBlt(hdc, 0, 0, WIDTH, HEIGHT, memdc, WIDTH * 4, 0, WIDTH, HEIGHT, SRCCOPY);
			Sleep(400);
			if (_kbhit())//아무 키나 눌리면 반복문을 빠져 나간다
				break;
		}
		break;
		DeleteDC(memdc);
		DeleteObject(bitmap);
		ReleaseDC(hWnd, hdc);
	}
}
int displayending(HWND hWnd, int dpi, HBITMAP image, int p1score, int p2score)//게임이 끝날 경우 승자와, 다시하기 이미지를 출력하는 함수
{
	int select = 0, winner;
	if (p2score < p1score)//승자 판단
		winner = 1;
	else if (p1score < p2score)
		winner = 2;
	else
		winner = 1;
	HDC hdc = GetDC(hWnd);
	HDC memdc = CreateCompatibleDC(hdc);
	HBITMAP bitmap = CreateCompatibleBitmap(hdc, WIDTH * 4, HEIGHT);
	SelectObject(memdc, bitmap);
	GetBMP(hdc, memdc, image);
	while (1)
	{
		if (GetAsyncKeyState(VK_RIGHT) & 0x0001 || GetAsyncKeyState(0x44) & 0x0001)//게임 다시하기/하지 않기를 입력받는다
		{
			select++;
			select %= 2;
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x0001 || GetAsyncKeyState(0x41) & 0x0001)
		{
			select--;
			if (select < 0)
				select += 2;
			select %= 2;
		}
		StretchBlt(hdc, 0, 0, WIDTH, HEIGHT, memdc, WIDTH * select + 2 * (WIDTH * (winner - 1)), 0, WIDTH, HEIGHT, SRCCOPY);//승자와, 다시하기 이미지를 출력한다
		if (GetAsyncKeyState(VK_SPACE) & 0x0001)//스페이스바가 눌리면 반복문을 빠져 나간다
			break;
	}
	return select;//다시하기/하지 않기를 선택한 것을 반환한다
}