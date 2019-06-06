#include "logic/Bordeldashcontroller.h"

#include <intermediary/thread.h>



#include <iostream>


#include <basic/list.h>
//#include <basic/calllist.h>

#include <basic/safepointer.h>


void fun(int *__callArg, int *__funArg)
{
	std::cout << ".";
}


int main()
{
	core::intermediary::Thread<void>::sleepMilliseconds(100); // na potrzeby debugowania w konsoli przy uzyciu qtcreatora - jest bug zwiazany z synchronizacja aplikacji





//	int *array = new int[10];
//	core::basic::SafePointer<int> pointer(array, core::basic::Cleaner::deleteObject);
//	core::basic::SafePointer<int> pointer2 = pointer;








//	core::basic::List<int> list;

//	for(int i = 0; i < 1000000; ++i)
//		list.pushBack(1);

//	list.pushBack(2);
//	list.pushBack(3);
//	list.pushBack(4);

//	list.pushFront(0);
//	list.pushFront(-1);
//	list.pushFront(-2);
//	list.pushFront(-3);
//	list.pushFront(-4);

//	for(core::basic::List<int>::Iterator i = list.getBegin(); i.isIndicated(); ++i)
//	{
//		int d = 2;
//	}
//	//	std::cout << i.__getItem() << std::endl;

//	core::basic::List<int>::Iterator i2 = list.getBegin();
//	core::basic::List<int>::Iterator i3 = i2;

//	list.remove(i3);
//	std::cout << i2.__getItem() << std::endl;

//	return 0;










//	core::basic::CallList<int, int> callList;

//	core::basic::CallList<int, int>::Indicator i0 = callList.add(&fun);
//	core::basic::CallList<int, int>::Indicator i0_2 = i0;

//	//callList.remove(i0);
//	//callList.remove(i0_2);

//	core::basic::CallList<int, int>::Indicator i1 = callList.add(&fun);
//	core::basic::CallList<int, int>::Indicator i2 = callList.add(&fun);
//	core::basic::CallList<int, int>::Indicator i3 = callList.add(&fun);

//	callList.clear();

//	callList.call();




	logic::BordeldashController controller;

	return (controller.run() ? 0 : 1);
}
