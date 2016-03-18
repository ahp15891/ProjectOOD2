#ifndef EXECUTIVE_HEADER
#define EXECUTIVE_HEADER
/////////////////////////////////////////////////////////////////////////////
// Display.cpp - For Displaying the data to the command line			   //
// ver 1.0                                                                 //
// ----------------------------------------------------------------------- //
// copyright © Aakash Patel, Spring 2015                                   //
// All rights granted provided that this notice is retained                //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2013                             //
// Application: Xml Reader   , 2015                                       //
// Author:     Aakash Patel, Syracuse University,apatel06@syr.edu		   //
/////////////////////////////////////////////////////////////////////////////
/*
*Module Operatipons:
*This class is the main class of the Xml Reader and Writee.
*It contains the main() method through which we execute all the methods.

*Executive Class has the following methods:

void return_element_id_value(std::string id, std::string value, XmlProcessing::XmlDocument &x_object)
void get_elements_tag(std::string tag,XmlProcessing::XmlDocument &x_object); 
void add_remove_element(std::string AddRemoveChild, std::string Parent, XmlProcessing::XmlDocument &x_object);
void add_child_empty_tree(XmlProcessing::XmlDocument &x_object, XmlProcessing::XmlDocument::sPtr child);
void get_attributes(XmlProcessing::XmlDocument::sPtr &element);
void get_childrent(XmlProcessing::XmlDocument&element, std::string tag);
void add_remove_attribute(std::pair<std::string, std::string>value, std::string tag, XmlProcessing::XmlDocument &x_object);

*Required Files:
--- Display.h, XmlElement.cpp, XmlDocument.cpp, XmlReader.cpp

* Maintenance History:
--version 1.0
*/
#include "../XmlDocument/XmlDocument/XmlDocument.h"
#include"../Display/display.h"
#include "../XmlReader/XmlReader/XmlReader.h"
#include <sstream>
class Executive{
public:
	Executive(){};
	~Executive(){};
	void return_element_id_value(std::string id, std::string value, XmlProcessing::XmlDocument &x_object); // requirement 5
	void get_elements_tag(std::string tag,XmlProcessing::XmlDocument &x_object); //For Requirement 6
	void add_remove_element(std::string AddRemoveChild, std::string Parent, XmlProcessing::XmlDocument &x_object);//Requirement 7
	void add_child_empty_tree(XmlProcessing::XmlDocument &x_object, XmlProcessing::XmlDocument::sPtr child);//Requirement 7
	void get_attributes(XmlProcessing::XmlDocument::sPtr &element);//Requirement 8
	void get_childrent(XmlProcessing::XmlDocument&element, std::string tag);//Requirement 8
	void add_remove_attribute(std::pair<std::string, std::string>value, std::string tag, XmlProcessing::XmlDocument &x_object);//Requirement 9
};
#endif