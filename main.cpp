#include <Novice.h>
#include <Vector2.h>
#include <cmath>
#include <Windows.h>

const char kWindowTitle[] = "LC1C_27_ヤマダ_ショウエイ_";

struct BALL {
    float posX;
    float posY;
    float speedX; // X方向の速度
    float speedY; // Y方向の速度
    float radius;

    Vector2 v;
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    Novice::Initialize(kWindowTitle, 640, 360);

    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    BALL ball{
        320.0f, 250.0f,
        5.0f, 5.0f, // X方向とY方向の初速度
        50.0f,
        Vector2(3.0f, 0.0f)
    };

    while (Novice::ProcessMessage() == 0) {
        Novice::BeginFrame();
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        // 移動処理
        ball.posX += ball.speedX;
        ball.posY += ball.speedY;

        // 壁での反射ともちっとする処理
        if (ball.posX >= 640 - ball.radius) {
            ball.posX = 640 - ball.radius;
            ball.speedX *= -1.0f; // 速度の減衰
        }
        else if (ball.posX <= 0 + ball.radius) {
            ball.posX = 0 + ball.radius;
            ball.speedX *= -1.0f;
        }

        if (ball.posY >= 360 - ball.radius) {
            ball.posY = 360 - ball.radius;
            ball.speedY *= -1.0f;
        }
        else if (ball.posY <= 0 + ball.radius) {
            ball.posY = 0 + ball.radius;
            ball.speedY *= -1.0f;
        }

        

        //描画
        Novice::DrawEllipse(
            static_cast<int>(ball.posX),
            static_cast<int>(ball.posY),
            static_cast<int>(ball.radius),
            static_cast<int>(ball.radius),
            0.0f, 0xffffffff, kFillModeSolid);

        Novice::EndFrame();

        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
            break;
        }
    }

    Novice::Finalize();
    return 0;
}
