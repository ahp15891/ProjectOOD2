/////////////////////////////////////////////////////////////////////////////
// Display.cpp - For Displaying the data to the command line			   //
// ver 1.0                                                                 //
// ----------------------------------------------------------------------- //
// copyright © Aakash Patel, Spring 2015                                   //
// All rights granted provided that this notice is retained                //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2013                             //
// Application: XML Reader	, 2015                                       //
// Author:     Aakash Patel, Syracuse University,apatel06@syr.edu		   //
////////////////////////////////////////////////////////////////////////////
#include "display.h"
//requirement 5 display output
void Display::requirement_5(XmlProcessing::XmlDocument::sPtr &data){
	
	if (data == NULL){
		std::cout << "  No Element contains the given ID and VALUE  " << std::endl << std::endl;
	}
	else{
		std::string str = "";
		str = data->toString();
		std::cout << str << std::endl << std::endl;
	}
}
//requirement 6 display output
void Display::requirement_6(std::vector<XmlProcessing::XmlDocument::sPtr> &data){
	if (data.size() == 0){
		std::cout << "  No Element with the given tag exists!  " << std::endl << std::endl;
	}
	else{
		for (size_t i = 0; i < data.size(); i++){
			std::string str = data[i]->toString();
			std::cout << str << std::endl << std::endl;
		}

	}
}
//requirement 7_1 display output
void Display::requirement_7_1(std::vector<XmlProcessing::XmlDocument::sPtr> &data){
	for (size_t i = 0; i < data.size(); i++){
		std::string str = data[i]->toString();
		std::cout << str << std::endl << std::endl;
	}

}
//requirement 7_2 display output
void Display::requirement_7_2(std::vector<XmlProcessing::XmlDocument::sPtr> &data){
	std::cout << "  Showing The tree after adding a child to empty tree: " << std::endl;
	std::string str = data[0]->toString();
	std::cout << str << std::endl << std::endl;

}
//requirement 8_1 display output
void Display::requirement_8_1(std::vector<std::pair<std::string, std::string>> &data){
	std::cout << "  Show attributes for the given element: " << std::endl;
	if (data.size() == 0){
		std::cout << "  No attributes for the given Elements are found!!!  " << std::endl << std::endl;
	}
	else{
		for (size_t i = 0; i < data.size(); i++){
			std::cout << "   ID =  " << data[i].first << "    VALUE =  " << data[i].second << std::endl << std::endl;
		}
	}

}
//requirement 8_2 display output
void Display::requirement_8_2(std::vector<XmlProcessing::XmlDocument::sPtr> &data){
	if (data.size() == 0){
		std::cout << "  The given element has not children!!!!!  " << std::endl << std::endl;
	}
	else{
		for (size_t i = 0; i < data.size(); i++){
			std::string str = data[i]->toString();
			std::cout << str << std::endl << std::endl;
		}
	}
}
//requirement 9 display output
void Display::requirement_9(std::vector<XmlProcessing::XmlDocument::sPtr> &data){
	for (size_t i = 0; i < data.size(); i++){
		std::string str = data[i]->toString();
		std::cout << str << std::endl << std::endl;
	}

}
#ifdef DISPLAY_XML
int main(){
	Display display_object;
	XmlProcessing::XmlDocument::sPtr temp;
	XmlProcessing::XmlDocument data_type;
	display_object.requirement_5(temp);
	std::vector<std::pair<std::string, std::string>> vect;
	std::vector<XmlProcessing::XmlDocument::sPtr> data;
	display_object.requirement_6(data);
	display_object.requirement_7_1(data);
	display_object.requirement_7_2(data);
	display_object.requirement_8_1(vect);
	 display_object.requirement_8_2(data);
	 display_object.requirement_9(data);

	return 1;
}
#endif