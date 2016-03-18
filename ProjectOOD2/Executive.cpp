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
#include"Executive.h"
#include <iostream>

/*
* -- Requirement 5 for getting the element for a particular Id and Value;
* -- will store the element in the sPtr pointer and pass it to display method.
*/
void Executive::return_element_id_value(std::string id, std::string value, XmlProcessing::XmlDocument &x_object){
	
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "************************ Demonstrating Requirement 5 ***************************" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "Please input the ID: " << id << "   \nPlease input the value: " << value << std::endl;
	XmlProcessing::XmlDocument::sPtr temp_pointer = x_object.get_attribute_element(id, value);
	Display::requirement_5(temp_pointer);
}
/*
* -- Requirement 6--
* -- will find all the elements in the xml with the given tag and return a vector
*/
void Executive::get_elements_tag(std::string tag, XmlProcessing::XmlDocument &x_object){
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "************************ Demonstrating Requirement 6 ***************************" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	x_object.select();
	std::cout << "Please enter the Tag you are looking for: " << tag << std::endl;
	std::vector<XmlProcessing::XmlDocument::sPtr> temp_vector;
	temp_vector = x_object.elements(tag).select();
	Display::requirement_6(temp_vector);
}
/*
* -- Requirement 7 --
* -- will add and remove children from the tag pointer we have passed
*/
void Executive::add_remove_element(std::string AddRemoveChild, std::string Parent, XmlProcessing::XmlDocument &x_object){
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "************************ Demonstrating Requirement 7 ***************************" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	XmlProcessing::XmlDocument::sPtr val;
	std::cout << "Enter tag to add child: " << AddRemoveChild << "   \nAdd the parent tag: " << Parent << std::endl;
	std::vector<XmlProcessing::XmlDocument::sPtr> temp_vector;
	temp_vector = x_object.element(Parent).select();
	if (temp_vector.size() == 0) {
		std::cout << "  Parent for the given tag not found " << std::endl << "   Can't Add or Remove Child because parent not found" << std::endl; return;
	}
	else{
		std::cout << "  Before adding the child to parent: " << std::endl;
		Display::requirement_7_1(temp_vector);
		std::cout << "  Adding the child to the Parent  " << std::endl;
		val = XmlProcessing::makeTaggedElement(AddRemoveChild);
		std::cout << "  After Adding the child  " << std::endl;
		temp_vector[0]->addChild(val);
		Display::requirement_7_1(temp_vector);
	}
	std::cout << "Enter tag to remove child:   " << AddRemoveChild << "   \nAdd the parent tag: " << Parent << std::endl;
	std::vector<XmlProcessing::XmlDocument::sPtr> child_vector = x_object.element(AddRemoveChild).select();
	val = child_vector[0];
	temp_vector[0]->removeChild(val);
	std::cout << "After removing from the xml:" << std::endl;
	Display::requirement_7_1(temp_vector);
}
/*
* -- Requirement 7--
* -- adds element to an empty tree
*/
void Executive::add_child_empty_tree(XmlProcessing::XmlDocument &x_object, XmlProcessing::XmlDocument::sPtr child){
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "************************ Demonstrating Requirement 7 ***************************" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	if (child->return_children()->size()==0){
		std::cout << "Enter the tag for the children to be add: " << child->value() << std::endl;
		std::vector<XmlProcessing::XmlDocument::sPtr>temp_vector;
		x_object.empty_tree(child);
		temp_vector = x_object.select();
		Display::requirement_7_2(temp_vector);
	}
	else{
		std::cout << " The given XML already has Root and Children!!!! " << std::endl;
	}

}
/*
* -- Requirement 8--
* -- will get the attributes for the given element pointer and store it in a vector
*/
void Executive::get_attributes(XmlProcessing::XmlDocument::sPtr &element){
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "************************ Demonstrating Requirement 8 ***************************" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::vector<std::pair<std::string, std::string>> temp;
	temp = XmlProcessing::XmlDocument::return_attributes(element);
	Display::requirement_8_1(temp);
}
/*
* -- Requirement 8--
* -- will get the children for the given pointer and return all the children that the element posesses
*/
void Executive::get_childrent(XmlProcessing::XmlDocument &element, std::string tag){
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "************************ Demonstrating Requirement 8 ***************************" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "Enter the tag for the children we need to find: " << tag << std::endl;
	element.select();
	std::vector<XmlProcessing::XmlDocument::sPtr> temp_vector;
	temp_vector = element.element(tag).children().select();
	Display::requirement_8_2(temp_vector);

}
/*
* -- Requirement 9--
* -- will add and remove attributes in the xml with the given tag and return a vector
*/
void Executive::add_remove_attribute(std::pair<std::string, std::string>value, std::string tag, XmlProcessing::XmlDocument &x_object){
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "************************ Demonstrating Requirement 9 ***************************" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	bool flag;
	std::cout << "<---Add Attribute--->" << std::endl;
	std::cout << "Enter the tag: " << tag << "\nEnter the Attribute key: " << value.first << "  \nEnter the Attribute Value : " << value.second << std::endl;
	x_object.select();
	std::vector<XmlProcessing::XmlDocument::sPtr> temp_vect;
	temp_vect = x_object.element(tag).select();
	if (temp_vect.size() == 0){
		std::cout << "No Element with the given tag found!" << std::endl;
		return;
	}
	else{
		flag = temp_vect[0]->type();
	 if (flag == false){
		std::cout << "Can't add element to a tag that can't support attributes" << std::endl;
		return;
	}
	else if (flag == true){
		temp_vect[0]->addAttrib(value.first, value.second);
		std::cout << "After adding the attributes to the given element: " << std::endl<< std::endl;

		Display::requirement_9(temp_vect);
	}

	std::cout << "<---Remove Attributes--->" << std::endl;
	std::cout << "Enter the tag: " << tag << "\nEnter the Attribute key: " << value.first << "\nEnter the Attribute Value : " << value.second << std::endl;
	std::vector<XmlProcessing::XmlDocument::sPtr> temp_vect1;
	temp_vect1 = x_object.element(tag).select();
	if (temp_vect1.size() == 0){
		std::cout << "No Element with the given tag found!" << std::endl;
		return;
	}
	temp_vect1[0]->removeAttrib(value.first);
	std::cout << "After removing the attributes to the given element: " << std::endl;

	Display::requirement_9(temp_vect);
	}
}
int main(int argv, char *argc[]){
	Executive exe_object;
	std::pair<std::string, std::string> temp_pair = { "arsenal", "aakash" };
	XmlProcessing::XmlDocument x_object;
	std::string file_name = argc[1];
	std::string new_file = argc[2];
	XmlProcessing::XmlDocument::sPtr doc_object;
	std::vector<XmlProcessing::XmlDocument::sPtr> temp_Vect;
	x_object = XmlProcessing::XmlDocument::XmlDocument(file_name, XmlProcessing::XmlDocument::sourceType::filename);
	temp_Vect = x_object.elements("catalog").select();
	doc_object = x_object.return_pDoc();
	if (temp_Vect.size() != 0){
	exe_object.return_element_id_value("desirability", "10", x_object);//call method for requirement 5
	exe_object.get_elements_tag("catalog", x_object);
	exe_object.add_remove_element("aakash", "catalog", x_object);
	exe_object.get_attributes(temp_Vect[0]);
	exe_object.get_childrent(x_object, "catalog");
	exe_object.add_remove_attribute(temp_pair, "catalog", x_object);
	exe_object.add_child_empty_tree(x_object, doc_object);
	x_object.save(new_file);
	}
	else{
			exe_object.add_child_empty_tree(x_object, doc_object);
	}
	
	return 0;
	
}