///////////////////////////////////////////////////////////////////
// XmlDocument.cpp - a container of XmlElement nodes             //
// Ver 1.2                                                       //
// Application: Help for CSE687 Pr#2, Spring 2015                //
// Platform:    Dell XPS 2720, Win 8.1 Pro, Visual Studio 2013   //
// Author:      Jim Fawcett, CST 4-187, 443-3948				 //
//				Aakash Patel,apatel06@syr.edu					 //
//              jfawcett@twcny.rr.com                            //
///////////////////////////////////////////////////////////////////

#include <iostream>
#include "XmlDocument.h"
#include <fstream>
#include <streambuf>
#include <string>
#include <cerrno>
using namespace XmlProcessing;
/*
* -- The XmlDocument() method will read the file into a string if the sourceType is a file
* -- If the sourceType is not a file then it directly pass the string to make the tree for that xml.
*/
XmlProcessing::XmlDocument::XmlDocument(const std::string& src, sourceType srcType)
{
	std::string file_data;
	std::string temp_string = "<Dir><path>/TestFile/Dir1</path><File><name>text1.txt</name><date>02/11/2012</date></File></Dir>";
	if (srcType == filename){
		std::ifstream in(src, std::ios::in | std::ios::binary);
		if (in.good()){
			file_data = std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
		}
	}
	else{
		file_data = temp_string;
	}
	pDocElement_ = makeDocElement();
	make_tree(file_data, pDocElement_);
	found_.push_back(pDocElement_);
}

/*
* -- The make_tree() method will make the tree and add children in the pDocElement
* -- Will add the ProcElement, CommentElement, TaggedElement, Attributes and TextElement
*/
void XmlProcessing::XmlDocument::make_tree(std::string &file, std::shared_ptr < AbstractXmlElement > temp){
	std::string text_ele = ""; std::string body = ""; std::string val = ""; std::string ele = "";
	std::shared_ptr < AbstractXmlElement > curr_node;
	XmlReader rdr(file);
	size_t x = file.find_first_of("<");	size_t y = file.find_first_of("\r");
	if (file.find("\r\n ") != std::string::npos){
		text_ele = file.substr(0, x); 
		if (text_ele.size() > 0 && y!=0){
		text_ele = text_ele.erase(y, (y + 7));
		temp->addChild(curr_node = makeTextElement(text_ele));
		}
	}
	else
		temp->addChild(curr_node = makeTextElement(file));
	while (rdr.next()){
		val = rdr.tag().c_str();
		ele = rdr.element().c_str();
		body = rdr.body().c_str();
		if (val.find("?xml") != std::string::npos)
			temp->addChild(curr_node = makeProcInstrElement(val));
		else if (val.find("!--") != std::string::npos)
			temp->addChild(curr_node = makeCommentElement(ele));
		else
			temp->addChild(curr_node = makeTaggedElement(val));
		XmlReader::attribElems attribs = rdr.attributes();
		for (size_t i = 0; i < attribs.size(); i++){
			curr_node->addAttrib(attribs[i].first.c_str(), attribs[i].second.c_str());
		}
		if (body.size()>0)
			make_tree(body, curr_node);
		rdr.position(rdr.xml().find('>', rdr.position()) + body.size());
			}
			
}
/*
* -- empty_tree() will add a element to epmty tree.
*/
bool XmlProcessing::XmlDocument::empty_tree(XmlProcessing::XmlDocument::sPtr value){
	XmlProcessing::XmlDocument::sPtr temp;
	std::string val = "<?xml version =""1.0""?>";
	temp = makeProcInstrElement(val);
//	std::string declaration = "<?xml version=""1.0""?>";
	return pDocElement_->addChild(temp);


}
/*
* -- element() will take a string as parameter which will check for the tag.
* -- std::move is called on found_ and take the value from found_ and put in a temporary value
* -- first_element method is called from here.
*/
XmlProcessing::XmlDocument& XmlProcessing::XmlDocument::element(const std::string& tag){
	std::vector<std::shared_ptr < AbstractXmlElement >> pointer_value(std::move(found_));
	for (size_t i = 0; i < pointer_value.size(); i++){
		first_element(tag, pointer_value[i]);
	}
	return *this;
}
/*
* -- first_element() will find the element we need to find based on the tag passed
* -- it will only return only the first element that is found 
*/
void  XmlProcessing::XmlDocument::first_element(const std::string&tag, sPtr val){
	if (val->value() == tag){
		//if (std::find(found_.begin(), found_.end(), val) == found_.end()){
		if (found_.size()==0){
			found_.push_back(val);
			return;
		}
	}
	std::vector<std::shared_ptr<AbstractXmlElement>> *curr_pointer = val->return_children();
	if (curr_pointer != NULL){
		for (size_t i = 0; i < curr_pointer->size(); i++){
			first_element(tag, (*curr_pointer)[i]);
		}

	}
}
//Select() method for moving the values from found_ using std::move
std::vector<XmlProcessing::XmlDocument::sPtr> XmlProcessing::XmlDocument::select(){
	std::vector<XmlProcessing::XmlDocument::sPtr> point(std::move(found_));
	std::vector<XmlProcessing::XmlDocument::sPtr> temp;
	found_.push_back(pDocElement_);
	temp = std::move(point);
	return temp;
}


/*
* -- elements will take tag and call first_elements method
*/
XmlProcessing::XmlDocument& XmlProcessing::XmlDocument::elements(const std::string& tag){
	
		std::vector<std::shared_ptr < AbstractXmlElement >> pointer_value(std::move(found_));
		for (size_t i = 0; i < pointer_value.size(); i++){
			first_elements(tag, pointer_value[i]);
		}
	return *this;
}
/*
* -- will find the elements with the required tag from the whole tree.
*/
void  XmlProcessing::XmlDocument::first_elements(const std::string&tag, sPtr val){
	if (val->value() == tag){
		if (found_.size() == 0||std::find(found_.begin(), found_.end(), val) == found_.end()){
			found_.push_back(val);
		}
	}
	std::vector<std::shared_ptr<AbstractXmlElement>> *curr_pointer = val->return_children();
	if (curr_pointer != NULL){
		for (size_t i = 0; i < curr_pointer->size(); i++){
			first_elements(tag, (*curr_pointer)[i]);
		}

	}
}
/*
* -- children will return pointers of all children for the given tag
*/
XmlProcessing::XmlDocument& XmlProcessing::XmlDocument::children(const std::string& tag){
	std::vector<std::shared_ptr < AbstractXmlElement >> pointer_value(std::move(found_));
	for (size_t i = 0; i < pointer_value.size(); i++){
		first_children(tag, pointer_value[i]);
		}
	return *this;

}
/*
* -- first_children will find the children for the given tag.
*/
void  XmlProcessing::XmlDocument::first_children(const std::string&tag, sPtr val){
	std::vector<std::shared_ptr<AbstractXmlElement>> *curr_pointer = val->return_children();
	if (curr_pointer != NULL){
	if (tag.empty() == true){
		for (size_t i = 0; i < curr_pointer->size(); i++){
			found_.push_back((*curr_pointer)[i]);
		}
	}
	else{
		
		for (size_t i = 0; i < curr_pointer->size(); i++){
			if ((*curr_pointer)[i]->value() == tag && std::find(found_.begin(), found_.end(), (*curr_pointer)[i])==found_.end()){
				found_.push_back((*curr_pointer)[i]);
			}
		}
	}
	}

}
/*
* -- descendents will take the tag and call first_descendents method to find the pointer to descendents.
*/
XmlProcessing::XmlDocument& XmlProcessing::XmlDocument::descendents(const std::string& tag){
	std::vector<std::shared_ptr < AbstractXmlElement >> pointer_value(std::move(found_));
	
	for (size_t i = 0; i < pointer_value.size(); i++){
		first_descendents(tag, pointer_value[i]);
	}
	return *this;

}
/*
* -- first_descendents will iterate through the tree and find the descendents for the tag
*/
void  XmlProcessing::XmlDocument::first_descendents(const std::string&tag, sPtr val){
	/*std::vector<std::shared_ptr<AbstractXmlElement>> *curr_pointer = val->return_children();
	if (curr_pointer != NULL){
		if (tag.empty() == true){
			for (size_t i = 0; i < curr_pointer->size(); i++){
				if (std::find(found_.begin(), found_.end(), (*curr_pointer)[i]) == found_.end()){
					found_.push_back((*curr_pointer)[i]);
					std::vector<std::shared_ptr<AbstractXmlElement>>*temp_child = (*curr_pointer)[i]->return_children();
					if (temp_child != NULL){
						for (size_t j = 0; j < temp_child->size(); j++){
							first_descendents(tag, (*temp_child)[j]);
						}
					}
				}
			}
		}

		else{
			for (size_t i = 0; i < curr_pointer->size(); i++){
				if ((*curr_pointer)[i]->value() == tag &&std::find(found_.begin(), found_.end(), (*curr_pointer)[i]) == found_.end()){
					found_.push_back((*curr_pointer)[i]);
					std::vector<std::shared_ptr<AbstractXmlElement>>*temp_child = (*curr_pointer)[i]->return_children();
					if (temp_child != NULL){
						for (size_t j = 0; j < temp_child->size(); j++){
							first_descendents(tag, (*temp_child)[j]);
						}
					}
				}

			}
		}
	}*/
	}
/*
* get_attribute_element will take id and value as the parameters and return the shared pointer of that attribute
*/
XmlProcessing::XmlDocument::sPtr XmlProcessing::XmlDocument::get_attribute_element(const std::string &id, const std::string &value){
	
	return find_attributes(id, value, pDocElement_);
}
/* finds the pointer with the given id and value the user is looking for */
XmlProcessing::XmlDocument::sPtr XmlProcessing::XmlDocument::find_attributes(std::string id, std::string value, sPtr doc_elem){
	sPtr temp;
	std::vector<std::pair<std::string, std::string>>*key_pair = doc_elem->return_attribute();
	if (key_pair != NULL){
		for (size_t i = 0; i < key_pair->size(); i++){
			if ((*key_pair)[i].first == id && (*key_pair)[i].second == value){
				temp = doc_elem;
				return temp;
			}
		}
	}
	std::vector<std::shared_ptr<AbstractXmlElement>> *temp_pointer = doc_elem->return_children();
	if (temp_pointer != NULL)
	{
		for (size_t i = 0; i < temp_pointer->size(); i++){
			std::shared_ptr<AbstractXmlElement> curr_pointer = find_attributes(id, value, (*temp_pointer)[i]);
			if (curr_pointer != NULL){
				temp = curr_pointer;
				return temp;
			}

		}
	}
	return temp;
}
//return the doc element
XmlProcessing::XmlDocument::sPtr XmlProcessing::XmlDocument::return_pDoc(){
	return pDocElement_;

}
/*
 * -- will return the a vector of the attribute for the given pointers
 */
std::vector<std::pair<std::string, std::string>> XmlProcessing::XmlDocument::return_attributes(const sPtr &tag){
	std::vector<std::pair<std::string, std::string>> temp_vector;
	if (tag->return_attribute() != NULL)
		return temp_vector = (*tag->return_attribute());
	else
		return temp_vector;

}
bool XmlProcessing::XmlDocument::save(std::string filename){
	if (filename == "")return false;
	std::ofstream of;
	of.open(filename, std::ofstream::trunc);
	if (of.fail())return false;
	of << this->toString();
	of.close();
	return true;

}
#ifdef XML_DOCUMENT_TEST
void main(){
	std::string file = "<Dir><path>/TestFile/Dir1</path><File><name>text1.txt</name><date>02/11/2012</date></File></Dir>";
	XmlProcessing::XmlDocument x_object(file);
	XmlProcessing::XmlDocument::sPtr temp = nullptr;
	x_object.element("File");
	x_object.elements("File");
	x_object.element("File").children();
	x_object.element("File").descendents();
	x_object.get_attribute_element("id", "book101");
	x_object.make_tree(file, temp);//temp = null;
	x_object.first_element("File", temp);//temp = null;
	x_object.first_elements("File", temp);//temp = null;
	x_object.first_children("File", temp);//temp = null;
	x_object.first_descendents("File", temp);//temp = null;

}
#endif