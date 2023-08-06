#include <iostream>
#include <Windows.h>
#include <thread>
#include <mutex>
#include <queue>

struct KeyInput {
    int key;
    double timestamp;
};

// 비동기 키보드 입력 처리 함수
void HandleKeyboardInput(std::atomic<bool>& running, std::queue<KeyInput>& inputQueue, std::mutex& mtx) {
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);

    while (running) {
        // ESC 키를 누르면 프로그램 종료
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            running = false;
        }

        // 다른 키 입력 처리
        // ...

        // 현재 시간 기록
        LARGE_INTEGER currentTime;
        QueryPerformanceCounter(&currentTime);
        double timestamp = static_cast<double>(currentTime.QuadPart) / static_cast<double>(frequency.QuadPart);

        // 입력된 키값 저장
        int currentKey = 0;
        for (int i = 0; i < 256; i++) {
            if (GetAsyncKeyState(i) & 0x8000) {
                currentKey = i;
                break;
            }
        }

        // 입력된 키와 시간을 큐에 저장
        std::lock_guard<std::mutex> lock(mtx);
        inputQueue.push({ currentKey, timestamp });
    }
}

int main() {
    std::atomic<bool> running(true);
    std::queue<KeyInput> inputQueue;
    std::mutex mtx;

    // 키보드 입력 처리를 비동기적으로 실행
    std::thread keyboardThread(HandleKeyboardInput, std::ref(running), std::ref(inputQueue), std::ref(mtx));

    // 메인 루프
    while (running) {
        // 비동기로 동작하는 키보드 입력 처리와 별개의 다른 작업 수행
        // ...

        // 메인 루프에서의 추가 작업
        // ...

        // 큐에서 키 입력과 입력 시간 가져오기
        std::lock_guard<std::mutex> lock(mtx);
        while (!inputQueue.empty()) {
            KeyInput input = inputQueue.front();
            inputQueue.pop();

            int currentKey = input.key;
            double currentTime = input.timestamp;
            std::cout << "입력된 키: " << currentKey << ", 입력 시간: " << currentTime << std::endl;
        }

        // 프레임 간격 대기 (예시로 30ms 간격으로 설정)
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }

    // 비동기 입력 처리가 완료될 때까지 대기
    keyboardThread.join();

    std::cout << "프로그램을 종료합니다." << std::endl;
    return 0;
}
