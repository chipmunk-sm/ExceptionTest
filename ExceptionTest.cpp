
#pragma warning( push )
#pragma warning( disable : 4365 ) // conversion from '' to ''
#pragma warning( disable : 4668 ) // is not defined as a preprocessor macro
#pragma warning( disable : 4710 ) // function not inlined
#pragma warning( disable : 4711 ) // selected for automatic inline expansion
#pragma warning( disable : 4820 ) // bytes padding added after data member
#pragma warning( disable : 5039 ) // pointer or reference to potentially throwing function passed to 'extern "C"' function under - EHc.Undefined behavior may occur if this function throws an exception.
#pragma warning( disable : 5264 ) // 'const' variable is not used

#include <iostream>
#include <string>
#include <map>
#include <atomic>
#include <thread>
#include <vector>
#include <mutex>
#include <exception>

#include <windows.h>

#pragma warning( pop )

#pragma warning( disable : 4710 ) // function not inlined


void proc_exception_handler(unsigned int u, EXCEPTION_POINTERS* pExp)
{
	UNREFERENCED_PARAMETER(pExp);
	UNREFERENCED_PARAMETER(u);
#if 0

	std::exception_ptr curr_excp = std::current_exception();
	if (curr_excp) {
		std::cerr << "Re-translate exception in proc_exception_handler rethrow_exception() " << std::endl;
		std::rethrow_exception(curr_excp);
	}

	std::cerr << "Re-translate exception in proc_exception_handler (Unexpected exception)" << std::endl;
	throw std::runtime_error("Unexpected exception");

#else
	try {
		std::rethrow_exception(std::current_exception());
	}
	catch (const std::exception&) {
		std::cerr << "Re-translate exception in proc_exception_handler rethrow_exception() " << std::endl;
		throw;
	}
	catch (...) {
		std::cerr << "Re-translate exception in proc_exception_handler (Unexpected exception)" << std::endl;
		throw "Unexpected exception";
	}
#endif
}

int main()
{

#if 1
	_set_se_translator(proc_exception_handler);

	try {
		std::cout << ">>>> 1 access violation start" << std::endl;
		
		//std::vector<uint8_t> d(10);
		//memset(d.data(), 0, 1024);

		*(int*)0 = 0;

		std::cout << ">>>> 1 access violation continue" << std::endl;
	}
	catch (const std::exception& ex) {
		std::cerr << "1 Try-catch(const std::exception& ex) typeid[" + std::string(typeid(ex).name()) << "] [" << ex.what() << "]" << std::endl;
	}
	catch (...) {
		try {
			std::rethrow_exception(std::current_exception());
		}
		catch (const std::exception& ex) {
			std::cerr << "1 Try-catch(const std::exception& ex) typeid[" + std::string(typeid(ex).name()) << "] [" << ex.what() << "]" << std::endl;
		}
		catch (...) {
			std::cerr << "1 Try-catch(...) typeid[Unexpected exception]" << std::endl;
		}
	}

	std::cout << std::endl << "-------------------------" << std::endl << std::endl;

	try {
		std::cout << ">>>> 2 divide by zero start" << std::endl;
		int x, y = 0;
		x = 5 / y;
		std::cout << ">>>> 2 divide by zero continue" << std::endl;
	}
	catch (const std::exception& ex) {
		std::cerr << "2 Try-catch(const std::exception& ex) typeid[" + std::string(typeid(ex).name()) << "] [" << ex.what() << "]" << std::endl;
	}
	catch (...) {
		try {
			std::rethrow_exception(std::current_exception());
		}
		catch (const std::exception& ex) {
			std::cerr << "2 Try-catch(const std::exception& ex) typeid[" + std::string(typeid(ex).name()) << "] [" << ex.what() << "]" << std::endl;
		}
		catch (...) {
			std::cerr << "2 Try-catch(...) typeid[Unexpected exception]" << std::endl;
		}
	}
	std::cout << std::endl << "-------------------------" << std::endl << std::endl;

#else

	//std::set_terminate([]()->void {proc_exception_handler(0, nullptr); });

	try {
		std::cout << ">>>> 3 access violation start" << std::endl;
		*(int*)0 = 0;
		std::cout << ">>>> 3 access violation continue" << std::endl;
	}
	catch (const std::exception& ex) {
		std::cerr << "3 Try-catch(const std::exception& ex) typeid[" + std::string(typeid(ex).name()) << "] [" << ex.what() << "]" << std::endl;
	}
	catch (...) {
		try {
			std::rethrow_exception(std::current_exception());
		}
		catch (const std::exception& ex) {
			std::cerr << "3 Try-catch(const std::exception& ex) typeid[" + std::string(typeid(ex).name()) << "] [" << ex.what() << "]" << std::endl;
		}
		catch (...) {
			std::cerr << "3 Try-catch(...) typeid[Unexpected exception]" << std::endl;
		}
	}

	std::cout << std::endl << "-------------------------" << std::endl << std::endl;

	try {
		std::cout << ">>>> 4 divide by zero start" << std::endl;
		int x, y = 0;
		x = 5 / y;
		std::cout << ">>>> 4 divide by zero continue" << std::endl;
	}
	catch (const std::exception& ex) {
		std::cerr << "4 Try-catch(const std::exception& ex) typeid[" + std::string(typeid(ex).name()) << "] [" << ex.what() << "]" << std::endl;
	}
	catch (...) {
		try {
			std::rethrow_exception(std::current_exception());
		}
		catch (const std::exception& ex) {
			std::cerr << "4 Try-catch(const std::exception& ex) typeid[" + std::string(typeid(ex).name()) << "] [" << ex.what() << "]" << std::endl;
		}
		catch (...) {
			std::cerr << "4 Try-catch(...) typeid[Unexpected exception]" << std::endl;
		}
	}

	std::cout << std::endl << "-------------------------" << std::endl << std::endl;

#endif

	std::cout << "> EXIT!" << std::endl;

	return 0;

}
