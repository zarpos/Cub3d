#include "./minilibx-linux/mlx.h"
#include "./include/cub3d.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define X_EVENT_KEY_PRESS 2

#define screenWidth 640
#define screenHeight 480
#define X_EVENT_KEY_EXIT 17
#define W 119
#define A 97
#define S 115
#define D 100

#define texWidth 64
#define texHeight 64
#define MAPWIDTH 24
#define MAPHEIGHT 24

typedef struct s_im
{
    void *img;
    int *data;

    int size_l;
    int bpp;
    int endian;
    int img_width;
    int img_height;
} t_im;

typedef struct s_info
{
    double playerPositionX;
    double playerPositionY;
    double directionVectorX;
    double directionVectorY;
    double planeX;
    double planeY;
    void *mlx;
    void *win;
    double moveSpeed;
    double rotSpeed;

    // textured에서 아래 세 변수가 추가됨.
    t_im img;
    int buf[screenHeight][screenWidth];
    int **texture;

} t_info;

int calculateAndSaveToMap(t_info *info);
void imageDraw(t_info *info);

// 바뀐 맵.
int worldMap[MAPWIDTH][MAPHEIGHT] =
    {
        {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4, 6, 4, 4, 6, 4, 6, 4, 4, 4, 6, 4},
        {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
        {8, 0, 3, 3, 0, 0, 0, 0, 0, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6},
        {8, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6},
        {8, 0, 3, 3, 0, 0, 0, 0, 0, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
        {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 4, 0, 0, 0, 0, 0, 6, 6, 6, 0, 6, 4, 6},
        {8, 8, 8, 8, 0, 8, 8, 8, 8, 8, 8, 4, 4, 4, 4, 4, 4, 6, 0, 0, 0, 0, 0, 6},
        {7, 7, 7, 7, 0, 7, 7, 7, 7, 0, 8, 0, 8, 0, 8, 0, 8, 4, 0, 4, 0, 6, 0, 6},
        {7, 7, 0, 0, 0, 0, 0, 0, 7, 8, 0, 8, 0, 8, 0, 8, 8, 6, 0, 0, 0, 0, 0, 6},
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 6, 0, 0, 0, 0, 0, 4},
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 6, 0, 6, 0, 6, 0, 6},
        {7, 7, 0, 0, 0, 0, 0, 0, 7, 8, 0, 8, 0, 8, 0, 8, 8, 6, 4, 6, 0, 6, 6, 6},
        {7, 7, 7, 7, 0, 7, 7, 7, 7, 8, 8, 4, 0, 6, 8, 4, 8, 3, 3, 3, 0, 3, 3, 3},
        {2, 2, 2, 2, 0, 2, 2, 2, 2, 4, 6, 4, 0, 0, 6, 0, 6, 3, 0, 0, 0, 0, 0, 3},
        {2, 2, 0, 0, 0, 0, 0, 2, 2, 4, 0, 0, 0, 0, 0, 0, 4, 3, 0, 0, 0, 0, 0, 3},
        {2, 0, 0, 0, 0, 0, 0, 0, 2, 4, 0, 0, 0, 0, 0, 0, 4, 3, 0, 0, 0, 0, 0, 3},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 4, 4, 4, 4, 4, 6, 0, 6, 3, 3, 0, 0, 0, 3, 3},
        {2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 1, 2, 2, 2, 6, 6, 0, 0, 5, 0, 5, 0, 5},
        {2, 2, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 2, 2, 0, 5, 0, 5, 0, 0, 0, 5, 5},
        {2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 5, 0, 5, 0, 5, 0, 5, 0, 5},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
        {2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 5, 0, 5, 0, 5, 0, 5, 0, 5},
        {2, 2, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 2, 2, 0, 5, 0, 5, 0, 0, 0, 5, 5},
        {2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 5, 5, 5, 5, 5, 5, 5, 5, 5}};

int main_loop(t_info *info)
{
    calculateAndSaveToMap(info);
    imageDraw(info);

    // warning 방지용.
    return (0);
}

void imageDraw(t_info *info)
{
    for (int y = 0; y < screenHeight; y++)
        for (int x = 0; x < screenWidth; x++)
            info->img.data[y * screenWidth + x] = info->buf[y][x];

    mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

int calculateAndSaveToMap(t_info *info)
{
    // 화면 생성 후 게임 루프 시작.
    // while문은 전체 프레임을 그려내고 입력을 읽는 역할을 함.
    for (int x = 0; x < screenWidth; x++)
    {
        for (int y = 0; y < screenHeight; y++)
        {
            info->buf[y][x] = 0xFFFFFF;
            info->buf[screenHeight - y - 1][x] = 0x000000;
            // buf[screenHeight - 1 ~ screenHeight - screenHeight][x] 를 칠해줌.
        }
    }
    int x;

    x = 0;
    while (x < screenWidth)
    {
        // cameraX 는 for문의 x값이 카메라 평면 상에 있을 때의 x좌표.
        double cameraX = (2 * x / (double)(screenWidth)) - 1;
        // cameraPlaneX == 0; cameraPlaneY == 0.66; dirVecX = -1; dirVecY = 0;
        // 광선의 방향은 방향벡터 + 카메라평면 * 배수.
        double rayDirectionX = info->directionVectorX + info->planeX * cameraX;
        double rayDirectionY = info->directionVectorY + info->planeY * cameraX;

        /*
            DDAgorithm
        */
        // 현재 player가 위치한 맵 내 위치.(which box of the map)
        int mapX = (int)(info->playerPositionX);
        int mapY = (int)(info->playerPositionY);

        // 현재 위치에서 다음 x사이드 또는 y사이드까지의 거리.
        // 이를 이하 '첫 번째 x면 및 y면'이라고 부를 것.
        double sideDistX;
        double sideDistY;

        // 아래 두 변수가 왜 저렇게 구해지는지에 대해서는 ii2r github #6 참고.
        // deltaDistX는 첫 번째 x면에서 그 다음 x면까지의 광선의 이동거리.
        // 이 경우 x는 1만큼 이동.
        // abs함수는 정수 절대값
        // fabs함수는 실수 절대값
        double deltaDistX = fabs(1 / rayDirectionX);
        // deltaDistY는 첫 번째 y면에서 그 다음 y면까지의 광선의 이동거리.
        // 이 경우 y는 1만큼 이동.
        double deltaDistY = fabs(1 / rayDirectionY);

        // 광선의 이동거리를 계산할 때 사용할 변수.
        double perpWallDist;

        // DDAgorithm은 반복문을 실행할 때마다 x, y방향으로 딱 한 칸씩 점프.
        // 광선의 방향에 따라 어느 방향으로 건너뛰는지 달라짐.
        // 그 정보는 stepX, Y에 +1, -1 둘 중 하나로 저장됨.
        int stepX;
        int stepY;

        /*
            hit은 벽과 부딪혔는지 판별하기 위한 변수임.
            부딪힌다는 것은 루프를 종료하기 위한 조건이 됨.
            만약 벽에 부딪혔는데 그게 x면에 부딪힌 거라면 side = 0임.
            y면에 부딪혔다면 1이 됨.
            한편 x면, y면은 어떤 칸의 경계가 되는 선을 의미함.
        */
        int hit = 0;
        int side;

        /*
            DDAgorithm을 시작하기 전에
            stepX, Y 그리고 sideDistX, Y에 값을 넣어주는 부분이다.
            rayDirectionX가 음수라는 말은 player기준 왼각이라는 뜻이고,
            양수라는 말은 player기준 오른각이라는 뜻이다.
            sideDistX의 값은 rayDirectionX 값이 양수인 경우
            광선의 오른쪽으로 이동하다 처음 만나는 x면까지의 거리가 된다.
            sideDistY의 값은 rayDirectionY 값이 양수인 경우
            광선의 위쪽으로 이동하다 처음 만나는 y면까지의 거리가 된다.
            rayDirectionX가 양수일 경우 sideDistX는
            mapX + 1에서 실제 위치 playerPositionX를 빼주고 deltaDistX를 곱한 결과다.
            반대의 경우 playerPositionX에서 mapX를 빼주고 deltaDistX를 곱한 결과다.
        */
        if (rayDirectionX < 0)
        {
            stepX = -1;
            sideDistX = (info->playerPositionX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - info->playerPositionX) * deltaDistX;
        }
        if (rayDirectionY < 0)
        {
            stepY = -1;
            sideDistY = (info->playerPositionY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - info->playerPositionY) * deltaDistY;
        }

        /*
            DDAgorithm 세팅을 완료했고, 이제 그것을 시작하는 부분.
            아래 while문은 `벽에 부딪힐 때까지` 매번 한 칸씩 광선 이동.
            반복할 때마다 x방향으로 한 칸 또는 y방향으로 한 칸 점프.
            만약 광선의 방향이 x축 방향과 완전히 일치한다면, x방향으로만 한 칸 점프하면 됨.
            광선이 점프할 때마다 <sideDistX, Y>에는 <deltaDistX, Y>가 더해지면서 업데이트됨.
        */
        while (hit == 0)
        {
            // 다음 map 박스로 이동하거나 x, y 방향 둘 중 하나로 이동한다.
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX; // stepX 는 1, -1 중 하나.
                side = 0;      // x면에 부딪혔다면 side = 0
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY; // stepY는 1, -1 중 하나.
                side = 1;      // y면에 부딪혔다면 side = 1
            }
            // ray가 벽을 만났는지 확인하는 작업
            if (worldMap[mapX][mapY] > 0)
                hit = 1;
        }
        /*
            벽을 만나 DDAgorithm이 완료됨.
            이제 광선의 시작점에서 벽까지의 이동거리를 계산할 차례임.
            광선의 시작점에서 벽까지의 이동거리는 벽의 높이를 계산하는 데 쓰임.
            H------------ :wall
            | \          \: 실제거리
            |  \         |: 벽에서 camera plane까지의 거리.
            -----P------- :camera plane
            P를 기준으로 벽까지의 실제거리를 사용한다면 fisheye 부작용이 나타남.
            따라서 벽으로부터 cameraPlane까지의 거리를 사용해야.
            이에 대한 자세한 설명은 로데브 설명 참고.
            따라서 아래 if-else문은 fisheye (side)effect를 방지하는 코드.
            (1 - stepX) / 2는 stepX가 -1이면 1이되고 1이면 0이 된다.(-1 or 0)
            해당 연산은 mapX - playerPositionX가 < 0 일 때, 즉 벽 밖으로 갈 때
            길이에 1을 더해주기 위한 코드이다.
            수직거리를 계산하는 방법은 이렇다.
            만약 광선이 처음으로 부딪힌 면이 x면이면
                mapX - playerPositionX + (1 - stepX / 2)는
                광선이 x방향으로 몇 칸이나 갔는지를 나타낸다.(정수 아니어도 됨.)
                rayDirectionX로 나눠주는 이유는 구해진 값이 수직거리보다 크기 때문.
            y면에 처음 부딪혔을 때도 같은 원리로 동작.
            mapX - playerPostionX가 음수더라도 음수인 rayDirectionX로 나누기 때문에
            계산된 값은 항상 양수임.
        */
        if (side == 0)
            perpWallDist = (mapX - info->playerPositionX + (1 - stepX) / 2) / rayDirectionX;
        else
            perpWallDist = (mapY - info->playerPositionY + (1 - stepY) / 2) / rayDirectionY;

        // 스크린에 그릴 line의 높이를 계산.
        int lineHeight = (int)(screenHeight / perpWallDist);
        /*
            이제 계산한 거리를 가지고 화면에 그려야 하는 선의 높이를 구할 수 있다.
            벽을 더 높게 그리거나 낮게 그리고 싶으면 2 * lineHeight 같은 값을 넣을 수도 있다.
            위에서 구한 lineHeight로부터 우리는 선을 그릴 위치의 시작점과 끝점을 구해낼 수 있다.
            만약에 벽의 범위 (0 ~ screenHeight)를 벗어나는 경우
            각각 0과 screenHeight - 1을 대입한다.
                +) drawStart와 End에 2로 나눈 값들을 더하는 이유는
                   screenHeight보다 drawEnd가 커지면 될까 안될까를 생각해보면 알 수 있다.
        */
        int drawStart = (-lineHeight / 2) + (screenHeight / 2);
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = (lineHeight / 2) + (screenHeight / 2);
        if (drawEnd >= screenHeight)
            drawEnd = screenHeight - 1;

        // texturing calculations
        // 1을 빼주는 이유는 0번째 텍스쳐도 0, 벽이 없어도 0이기 때문.
        // 1을 빼지 않는다면 어떻게 될까?
        // 아마 시작하자마자 뒷방향을 보고 앞으로 걸어나가려고 하면
        // segmentation fault가 뜰 것이다.
        int texNum = worldMap[mapX][mapY] - 1;
        // int textNum = worldMap[mapX][mapY];

        // wallX의 값은 벽의 x면과 부딪힌 경우(side == 0)
        // 벽의 Y좌표가 된다.
        // wallX의 값은 텍스처의 x좌표에 대해서만 사용한다.
        double wallX;
        if (side == 0)
            wallX = info->playerPositionY + perpWallDist * rayDirectionY;
        else
            wallX = info->playerPositionX + perpWallDist * rayDirectionX;
        wallX -= floor(wallX);

        // texX는 texture의 x좌표를 나타낸다.
        // x coordinate on the texture
        int texX = (int)(wallX * (double)texWidth);
        if (side == 0 && rayDirectionX > 0)
            texX = texWidth - texX - 1;
        if (side == 1 && rayDirectionY < 0)
            texX = texWidth - texX - 1;

        /*
            texY를 지정하는 반복문.
            step은 스크린 픽셀당 texture 좌표를 얼마나 증가시켜줄 건지를 결정.
            buffer[y][x]에 넣을 color는 texture 배열에서 가져온다.
        */
        // How much to increase the texture coordinate perscreen pixel
        double step = 1.0 * texHeight / lineHeight;
        // Starting texture coordinate
        double texPos = (drawStart - screenHeight / 2 + lineHeight / 2) * step;
        for (int y = drawStart; y < drawEnd; y++)
        {
            // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
            int texY = (int)texPos & (texHeight - 1);
            texPos += step;
            int color = info->texture[texNum][texHeight * texY + texX];
            // 광선이 벽의 y면에 부딪힌 경우(side == 1).
            // 조명표현을 위해 색상을 더 검게 만든다.
            // 이진수를 2로 나눔으로써 RGB값을 반감시킨다.
            // 시프트 연산을 하고 01111111 01111111 01111111(835711)을 & 연산하면
            // 어두운 값을 줄 수 있다는데 그냥 외워야 쓰것다.
            if (side == 1)
                color = (color >> 1) & 8355711;
            info->buf[y][x] = color;
        }
        x++;
    }
    return (0);
}

int key_press(int key, t_info *info)
{
    // WS
    // TODO: refactor

    if (key == W)
    {
        if (!worldMap[(int)(info->playerPositionX + info->directionVectorX * info->moveSpeed)][(int)(info->playerPositionY)])
            info->playerPositionX += info->directionVectorX * info->moveSpeed;
        if (!worldMap[(int)(info->playerPositionX)][(int)(info->playerPositionY + info->directionVectorY * info->moveSpeed)])
            info->playerPositionY += info->directionVectorY * info->moveSpeed;
    }

    if (key == S)
    {
        if (!worldMap[(int)(info->playerPositionX - info->directionVectorX * info->moveSpeed)][(int)(info->playerPositionY)])
            info->playerPositionX -= info->directionVectorX * info->moveSpeed;
        if (!worldMap[(int)(info->playerPositionX)][(int)(info->playerPositionY - info->directionVectorY * info->moveSpeed)])
            info->playerPositionY -= info->directionVectorY * info->moveSpeed;
    }

    // AD

    // TODO: refactor
    if (key == A)
    {
        double oldDirectionX = info->directionVectorX;
        info->directionVectorX = info->directionVectorX * cos(info->rotSpeed) - info->directionVectorY * sin(info->rotSpeed);
        info->directionVectorY = oldDirectionX * sin(info->rotSpeed) + info->directionVectorY * cos(info->rotSpeed);
        double oldPlaneX = info->planeX;
        info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
        info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
    }

    if (key == D)
    {
        double oldDirectionX = info->directionVectorX;
        info->directionVectorX = info->directionVectorX * cos(-info->rotSpeed) - info->directionVectorY * sin(-info->rotSpeed);
        info->directionVectorY = oldDirectionX * sin(-info->rotSpeed) + info->directionVectorY * cos(-info->rotSpeed);
        double oldPlaneX = info->planeX;
        info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
        info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
    }
    if (key == K_ESC)
        exit(0);
    return (0);
}

/*
    https://42kchoi.tistory.com/229?category=886844
    위 링크에서 설명했듯이 mlx_png_file_to_image는 메모리 누수 이슈가 있기 때문에,
    mlx_xpm_file_to_image를 사용한다.
    참고로 여기서 path는 상대경로다.
*/
void load_image(t_info *info, int *texture, char *path, t_im *img)
{
    printf("NUM %d\n", img->img_height);
    printf("Loading image from path: %s\n", path);
    img->img = mlx_xpm_file_to_image(info->mlx, path, &img->img_width, &img->img_height);
    if (img->img == NULL)
    {
        printf("Error loading image: %s\n", path);
        return;
    }

    img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
    if (img->data == NULL)
    {
        printf("Error getting data address for image: %s\n", path);
        mlx_destroy_image(info->mlx, img->img);
        return;
    }

    for (int y = 0; y < img->img_height; y++)
    {
        for (int x = 0; x < img->img_width; x++)
        {
            texture[img->img_width * y + x] = img->data[img->img_width * y + x];
        }
    }
    mlx_destroy_image(info->mlx, img->img);
}

void load_texture(t_info *info)
{
    t_im img;

    load_image(info, info->texture[0], "./src/sprites/wood.xpm", &img);
    load_image(info, info->texture[1], "./src/sprites/redbrick.xpm", &img);
    load_image(info, info->texture[2], "./src/sprites/purplestone.xpm", &img);
    load_image(info, info->texture[3], "./src/sprites/mossy.xpm", &img);
    load_image(info, info->texture[4], "./src/sprites/redbrick.xpm", &img);
    load_image(info, info->texture[5], "./src/sprites/mossy.xpm", &img);
    load_image(info, info->texture[6], "./src/sprites/wood.xpm", &img);
    load_image(info, info->texture[7], "./src/sprites/purplestone.xpm", &img);
}

int main()
{
    t_info info;
    info.mlx = mlx_init();

    // info는 아래 필드 모두를 가지고 있다.
    info.playerPositionX = 2.0;
    info.playerPositionY = 1.5;
    info.directionVectorX = -1.0;
    info.directionVectorY = 0.0;
    info.planeX = 0.0;
    info.planeY = 0.66;
    info.moveSpeed = 0.05;
    info.rotSpeed = 0.05;

    if (!(info.texture = (int **)malloc(sizeof(int *) * 8)))
        return (-1);
    for (int i = 0; i < 8; i++)
        if (!(info.texture[i] = (int *)malloc(sizeof(int) * (texHeight * texWidth))))
            return (-1);

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < texHeight * texWidth; j++)
            info.texture[i][j] = 0;

    /*
        info.texture 변수는 다음과 같이 선언돼 있는데,
            int        texture[8][texHeight * texWidth];
        이것이 의미하는 바는 총 8가지 종류의 텍스쳐를 저장할 수 있고,
        그 크기가 texHeight * texWidth 라는 뜻이다.
    */
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < texHeight * texWidth; j++)
            info.texture[i][j] = 0;

    load_texture(&info);

    // textured에서 추가된 코드 세 줄.
    info.win = mlx_new_window(info.mlx, screenWidth, screenHeight, "mlx");
    info.img.img = mlx_new_image(info.mlx, screenWidth, screenHeight);
    info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.size_l, &info.img.endian);

    // 아래 코드들이 무슨 역할을 하는 지 궁금하다면 아래 링크에서 정리해둔 내용을 보자.
    // https://42kchoi.tistory.com/229
    mlx_loop_hook(info.mlx, &main_loop, &info);
    mlx_hook(info.win, X_EVENT_KEY_PRESS, 1L << 0, &key_press, &info);
    mlx_loop(info.mlx);
}