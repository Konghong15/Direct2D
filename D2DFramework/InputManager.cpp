#include <iostream>
#include <Windows.h>
#include <thread>
#include <mutex>
#include <queue>

struct KeyInput {
    int key;
    double timestamp;
};

// �񵿱� Ű���� �Է� ó�� �Լ�
void HandleKeyboardInput(std::atomic<bool>& running, std::queue<KeyInput>& inputQueue, std::mutex& mtx) {
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);

    while (running) {
        // ESC Ű�� ������ ���α׷� ����
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            running = false;
        }

        // �ٸ� Ű �Է� ó��
        // ...

        // ���� �ð� ���
        LARGE_INTEGER currentTime;
        QueryPerformanceCounter(&currentTime);
        double timestamp = static_cast<double>(currentTime.QuadPart) / static_cast<double>(frequency.QuadPart);

        // �Էµ� Ű�� ����
        int currentKey = 0;
        for (int i = 0; i < 256; i++) {
            if (GetAsyncKeyState(i) & 0x8000) {
                currentKey = i;
                break;
            }
        }

        // �Էµ� Ű�� �ð��� ť�� ����
        std::lock_guard<std::mutex> lock(mtx);
        inputQueue.push({ currentKey, timestamp });
    }
}

int main() {
    std::atomic<bool> running(true);
    std::queue<KeyInput> inputQueue;
    std::mutex mtx;

    // Ű���� �Է� ó���� �񵿱������� ����
    std::thread keyboardThread(HandleKeyboardInput, std::ref(running), std::ref(inputQueue), std::ref(mtx));

    // ���� ����
    while (running) {
        // �񵿱�� �����ϴ� Ű���� �Է� ó���� ������ �ٸ� �۾� ����
        // ...

        // ���� ���������� �߰� �۾�
        // ...

        // ť���� Ű �Է°� �Է� �ð� ��������
        std::lock_guard<std::mutex> lock(mtx);
        while (!inputQueue.empty()) {
            KeyInput input = inputQueue.front();
            inputQueue.pop();

            int currentKey = input.key;
            double currentTime = input.timestamp;
            std::cout << "�Էµ� Ű: " << currentKey << ", �Է� �ð�: " << currentTime << std::endl;
        }

        // ������ ���� ��� (���÷� 30ms �������� ����)
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }

    // �񵿱� �Է� ó���� �Ϸ�� ������ ���
    keyboardThread.join();

    std::cout << "���α׷��� �����մϴ�." << std::endl;
    return 0;
}
