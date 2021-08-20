
#ifndef ABU_STRING
#define ABU_STRING
#include <string.h>
namespace abu {

	template <typename char_t = char>
	class abu_string
	{
	private:
		
		 unsigned long long length;
		 unsigned long long capacity;
		 char_t* pStr;
		
	public:
		
#pragma region operator= overload
		bool operator=(const char_t* str){
			
			__Alloc(str);
			return true;
		}

		bool operator=(char_t* str) {
			 
			__Alloc(str);
			return true;
		}

		bool operator=(abu_string& str) {
			__AllocObj(str);
			return true;
		}

		bool operator=(const abu_string& str) {
			this->~abu_string();
			__AllocObj(str);
			return true;
		}
#pragma endregion
	// this->capacity - this->length = size of the string;
#pragma region operator+ overload

		abu_string& operator+(const char_t* const str) {
			char_t* const tempStr = new char_t[this->length];
			strcpy_s(tempStr,this->length, this->pStr);
			this->capacity = strlen(str) + this->capacity;
			this->length = this->capacity + 1;
			this->pStr = new char_t[this->length];
			strcpy_s(this->pStr, this->length, tempStr);
			strcat_s(pStr, this->capacity - this->length, str);
			delete[] tempStr;
			return *this;
		}
		
		abu_string& operator+(char_t* str) {
			char_t* const tempStr = new char_t[this->length];
			strcpy_s(tempStr, this->length, this->pStr);

			this->capacity = strlen(str) + this->capacity;
			this->length = this->capacity + 1;
			this->pStr = new char_t[this->length];
			strcpy_s(this->pStr, this->length, tempStr);

			strcat_s(pStr, this->capacity - this->length, str);
			delete[] tempStr;
			return *this;
		}

		abu_string& operator+(abu_string& str) {
			size_t szCapacity2nd = strlen(str.pStr);
			char_t* const firstStr = new char_t[this->length];
			strcpy_s(firstStr, this->length, this->pStr);
			char_t* const secondStr = new char_t[szCapacity2nd + 1];
			strcpy_s(secondStr, this->length, str.pStr);
			this->capacity = this->capacity + szCapacity2nd;
			this->length = this->capacity + 1;
			this->pStr = new char_t[this->length];
			strcpy_s(this->pStr, this->length, firstStr);
			strcat_s(this->pStr, this->length, secondStr);
			delete[] firstStr;
			delete[] secondStr;
			return *this;
		}

		abu_string& operator+(const abu_string& str) {
			size_t szCapacity2nd = strlen(str.pStr);
			char_t* const firstStr = new char_t[this->length];
			strcpy_s(firstStr, this->length, this->pStr);
			char_t* const secondStr = new char_t[szCapacity2nd + 1];
			strcpy_s(secondStr, this->length, str.pStr);
			this->capacity = this->capacity + szCapacity2nd;
			this->length = this->capacity + 1;
			this->pStr = new char_t[this->length];
			strcpy_s(this->pStr, this->length, firstStr);
			strcat_s(this->pStr, this->length, secondStr);
			delete[] firstStr;
			delete[] secondStr;
			return *this;
		}

		


#pragma endregion


#pragma region Constructors
		abu_string(const abu_string& str) {
			__AllocObj(str);
		}

		abu_string(abu_string& str) {
			__AllocObj(str);
		} 
		
		abu_string(const char_t* str) {
			__Alloc(str);
		};
		
		abu_string(char_t* str) {
			__Alloc(str);
		};

		abu_string(){
			__Alloc("");
		}

#pragma endregion

#pragma region Memory allocation
		abu_string& __Alloc(const char_t* str) {
			this->capacity = strlen(str);
			this->length = this->capacity + 1;
			this->pStr = new char_t[this->length];
			strcpy_s(this->pStr, this->length, str);
			return *this;
		}

		abu_string& __AllocObj(const abu_string& str) {
			char_t* const temp = new char_t[str.length];
			strcpy_s(temp, str.length, str.pStr);

			this->capacity = str.capacity;
			this->length = this->capacity + 1;
			this->pStr = new char_t[this->length];
			strcpy_s(this->pStr, this->length, temp);
			delete[] temp;
			return *this;
		}
#pragma endregion

#pragma region Deconstructors
		~abu_string() {
			delete[] this->pStr;
			this->capacity = 0;
			this->length = 0;
		}
#pragma endregion

	};

	
	
	typedef abu_string<char> string;
	typedef abu_string<wchar_t> wstring;

}

#endif