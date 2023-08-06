#include <iostream>
#include <chrono>
#include <thread>
#include <future>
#include <vector>
#include <queue>
#include <conio.h>

struct InputData {
	char key;
	std::chrono::system_clock::time_point timestamp;

	InputData(char k, const std::chrono::system_clock::time_point& t)
		: key(k), timestamp(t) {}
};

// �񵿱�� Ű���� �Է��� ó���ϴ� �Լ�
std::queue<InputData> HandleKeyboardInput() {
	std::queue<InputData> inputDataList;

	while (true) {
		if (_kbhit()) {
			char ch = _getch();

			// 'q'�� ������ ���α׷� ����
			if (ch == 'q' || ch == 'Q') {
				break;
			}

			// ���� �ð��� �Էµ� Ű�� ����
			auto now = std::chrono::system_clock::now();
			inputDataList.push({ ch, now });
		}
	}

	return inputDataList;
}

int main() {
	// Ű���� �Է� ó���� �񵿱������� ����
	std::future<std::queue<InputData>> keyboardFuture = std::async(std::launch::async, HandleKeyboardInput);

	// �����Ӹ��� �Էµ� ��� ��ȸ
	while (true) {
		// �񵿱�� �����ϴ� Ű���� �Է� ó���� ������ �ٸ� �۾� ����
		// ...

		// �Էµ� ��� ��ȸ
		if (keyboardFuture.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready) {
			// �񵿱� �Է� ó���� �Ϸ�� ���
			std::vector<InputData> inputDataList = keyboardFuture.get();
			for (const auto& data : inputDataList) {
				std::cout << "Key: " << data.key << ", Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(data.timestamp.time_since_epoch()).count() << "ms\n";
			}

			// ���ο� �񵿱� Ű���� �Է� ó�� ����
			keyboardFuture = std::async(std::launch::async, HandleKeyboardInput);
		}
		else {
			// ���� �񵿱� �Է� ó���� �Ϸ���� ���� ���
			std::cout << "Waiting for keyboard input...\n";
		}

		// ������ ���� ��� (���÷� 30ms �������� ����)
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}

	std::cout << "���α׷��� �����մϴ�." << std::endl;
	return 0;
}
