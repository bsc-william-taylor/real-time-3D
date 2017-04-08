
#include "Demo.h"

int main(int argc, const char * argv) 
{
	Demo * Example = new Demo();

	Example->SetWindowSize(0, 0, 1600, 900);
	Example->SetRedrawRate(60);
	Example->HideConsole();
	Example->Execute();

	delete(Example);
	return NULL;
}