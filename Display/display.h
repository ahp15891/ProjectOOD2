#ifndef DISPLAY
#define DISPLAY
/////////////////////////////////////////////////////////////////////////////
// Display.cpp - For Displaying the data to the command line			   //
// ver 1.0                                                                 //
// ----------------------------------------------------------------------- //
// copyright © Aakash Patel, Spring 2015                                   //
// All rights granted provided that this notice is retained                //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2013                             //
// Application: Xml Reader and Writer, 2015                                //
// Author:     Aakash Patel, Syracuse University,apatel06@syr.edu		   //
/////////////////////////////////////////////////////////////////////////////
/*
*Module Operatipons:
*
*This class is for displaying the output the user on commandline
*in a presentable way which makes it easy for the user to understand.

*This class has the following methods: Also Public Interface


static void requirement_5(XmlProcessing::XmlDocument::sPtr &data);							
static void requirement_6(std::vector<XmlProcessing::XmlDocument::sPtr> &data);				
static void requirement_7_1(std::vector<XmlProcessing::XmlDocument::sPtr> &data);			
static void requirement_7_2(XmlProcessing::XmlDocument &data);								
static void requirement_8_1(std::vector<std::pair<std::string, std::string>> &data);		
static void requirement_8_2(std::vector<XmlProcessing::XmlDocument::sPtr> &data);			
static void requirement_9(std::vector<XmlProcessing::XmlDocument::sPtr> &data);

*Required Files:
-- XmlDocument

* Maintenance History:
--version 1.0
*/
#include "../XmlDocument/XmlDocument/XmlDocument.h"
#include <sstream>
#include <iostream>
class Display{
public:
	Display(){};
	~Display(){};
	static void requirement_5(XmlProcessing::XmlDocument::sPtr &data);							//show out for requirement 5
	static void requirement_6(std::vector<XmlProcessing::XmlDocument::sPtr> &data);				//show out for requirement 6
	static void requirement_7_1(std::vector<XmlProcessing::XmlDocument::sPtr> &data);			//show out for requirement 7_1
	static void requirement_7_2(std::vector<XmlProcessing::XmlDocument::sPtr> &data);								//show out for requirement 7_2
	static void requirement_8_1(std::vector<std::pair<std::string, std::string>> &data);		//show out for requirement 8_1
	static void requirement_8_2(std::vector<XmlProcessing::XmlDocument::sPtr> &data);			//show out for requirement 8_2
	static void requirement_9(std::vector<XmlProcessing::XmlDocument::sPtr> &data);				//show out for requirement 9

};
#endif 