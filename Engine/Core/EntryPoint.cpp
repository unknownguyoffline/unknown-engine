#include <Core/Application.hpp>
#include <Core/EntryPoint.hpp>

int main(int argv, char** argc)
{
	Unk::Application* application = Unk::CreateApplication(argv, argc);
	application->Run();
	delete application;
	return 0;
}