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

// 비동기로 키보드 입력을 처리하는 함수
std::queue<InputData> HandleKeyboardInput() {
	std::queue<InputData> inputDataList;

	while (true) {
		if (_kbhit()) {
			char ch = _getch();

			// 'q'를 누르면 프로그램 종료
			if (ch == 'q' || ch == 'Q') {
				break;
			}

			// 현재 시간과 입력된 키를 저장
			auto now = std::chrono::system_clock::now();
			inputDataList.push({ ch, now });
		}
	}

	return inputDataList;
}

int main() {
	// 키보드 입력 처리를 비동기적으로 실행
	std::future<std::queue<InputData>> keyboardFuture = std::async(std::launch::async, HandleKeyboardInput);

	// 프레임마다 입력된 목록 조회
	while (true) {
		// 비동기로 동작하는 키보드 입력 처리와 별개의 다른 작업 수행
		// ...

		// 입력된 목록 조회
		if (keyboardFuture.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready) {
			// 비동기 입력 처리가 완료된 경우
			std::vector<InputData> inputDataList = keyboardFuture.get();
			for (const auto& data : inputDataList) {
				std::cout << "Key: " << data.key << ", Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(data.timestamp.time_since_epoch()).count() << "ms\n";
			}

			// 새로운 비동기 키보드 입력 처리 시작
			keyboardFuture = std::async(std::launch::async, HandleKeyboardInput);
		}
		else {
			// 아직 비동기 입력 처리가 완료되지 않은 경우
			std::cout << "Waiting for keyboard input...\n";
		}

		// 프레임 간격 대기 (예시로 30ms 간격으로 설정)
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}

	std::cout << "프로그램을 종료합니다." << std::endl;
	return 0;
}
