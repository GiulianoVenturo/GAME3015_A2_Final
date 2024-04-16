#pragma once
#include "stddef.h"

namespace NonCopyable
{
	class Singleton {
	private:



		static Singleton*

			// static pointer which will points 
			//to the instance of this class
			instancePtr;

		// Default constructor
		Singleton()
		{
		}

	public:

		// deleting copy constructor
		Singleton(const Singleton& obj)
			= delete;

		/*
		  getInstance() is a static method that returns an
		  instance when it is invoked. It returns the same
		  instance if it is invoked more than once as an instance
		  of Singleton class is already created. It is static
		  because we have to invoke this method without any object
		  of Singleton class and static method can be invoked
		  without object of class

		  As constructor is private so we cannot create object of
		  Singleton class without a static method as they can be
		  called without objects. We have to create an instance of
		  this Singleton class by using getInstance() method.
		*/
		static Singleton* getInstance()
		{
			// If there is no instance of class
			// then we can create an instance.
			if (instancePtr == NULL)
			{
				// We can access private members 
				// within the class.
				instancePtr = new Singleton();

				// returning the instance pointer
				return instancePtr;
			}
			else
			{
				// if instancePtr != NULL that means 
				// the class already have an instance. 
				// So, we are returning that instance 
				// and not creating new one.
				return instancePtr;
			}
		}

		class  Singleton2
		{
		protected:

			Singleton2() {}

			~Singleton2() {}

		private:

			Singleton2(const Singleton2&);

			Singleton2& operator =(const Singleton2&);
		};
	};
}
#pragma endregion