#ifndef XMLDOCUMENT_H
#define XMLDOCUMENT_H
///////////////////////////////////////////////////////////////////
// XmlDocument.h - a container of XmlElement nodes               //
// Ver 1.2                                                       //
// Application: Help for CSE687 Pr#2, Spring 2015                //
// Platform:    Dell XPS 2720, Win 8.1 Pro, Visual Studio 2013   //
// Author:      Jim Fawcett, CST 4-187, 443-3948                 //
//              jfawcett@twcny.rr.com                            //
///////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package is intended to help students in CSE687 - Object Oriented Design
* get started with Project #2 - XML Document Model.  It uses C++11 constructs,
* most noteably std::shared_ptr.  The XML Document Model is essentially
* a program-friendly wrapper around an Abstract Syntax Tree (AST) used to
* contain the results of parsing XML markup.
*
* Abstract Syntax Trees, defined in this package, are unordered trees with 
* two types of nodes:
*   Terminal nodes     - nodes with no children
*   Non-Terminal nodes - nodes which may have a finite number of children
* They are often used to contain the results of parsing some language.
*
* The elements defined in the companion package, XmlElement, will be used in
* the AST defined in this package.  They are:
*   AbstractXmlElement - base for all the XML Element types
*   DocElement         - XML element with children designed to hold prologue, Xml root, and epilogue
*   TaggedElement      - XML element with tag, attributes, child elements
*   TextElement        - XML element with only text, no markup
*   CommentElement     - XML element with comment markup and text
*   ProcInstrElement   - XML element with markup and attributes but no children
*   XmlDeclarElement   - XML declaration element with attributes
*
* Required Files:
* ---------------
*   - XmlDocument.h, XmlDocument.cpp, 
*     XmlElement.h, XmlElement.cpp
*
* Build Process:
* --------------
*   devenv AST.sln /debug rebuild
*
* Maintenance History:
* --------------------
* ver 1.3 : 27 March 2015
* Added Methods:
*	make_tree()
*	first_element()
*	first_elements()
*	first_children()
*	first_descendents
*	get_attribute_element()
*	find_attributes()
*	return_attribute()
*
* ver 1.2 : 21 Feb 15
* - modified these comments
* ver 1.1 : 14 Feb 15
* - minor changes to comments, method arguments
* Ver 1.0 : 11 Feb 15
* - first release
* 
* ToDo:
* -----
* This is the beginning of an XmlDocument class for Project #2.  
* It lays out a suggested design, which you are not compelled to follow.
* If it helps then use it.  If not you don't have to.
*
* Note that I've simply roughed in a design that is similar to that
* used in the .Net Framework XDocument class.
*/

#include <memory>
#include <string>
#include <algorithm>
#include "../XmlElement/XmlElement.h"
#include "../../XmlReader/XmlReader/XmlReader.h"
namespace XmlProcessing
{
  class XmlDocument
  {
  public:
    using sPtr = std::shared_ptr < AbstractXmlElement > ;
	XmlDocument(){

	};
	~XmlDocument(){

	};
    enum sourceType { string, filename };

    XmlDocument(const std::string& src, sourceType srcType=string);
    
    // queries return XmlDocument references so they can be chained, e.g., doc.element("foobar").descendents();

    XmlDocument& element(const std::string& tag);           // found_[0] contains first element (DFS order) with tag
    XmlDocument& elements(const std::string& tag);          // found_ contains all elements with tag
    XmlDocument& children(const std::string& tag = "");     // found_ contains sPtrs to children of prior found_[0] 
    XmlDocument& descendents(const std::string& tag = "");  // found_ contains sPtrs to descendents of prior found_[0]
    std::vector<sPtr> select();                            // return reference to found_.  Use std::move(found_) to clear found_
	void make_tree(std::string &file, sPtr temp);			//method to make the XML Tree
	void first_element(const std::string&tag, sPtr val);	//finds the first element we are looking for
	void first_elements(const std::string&tag, sPtr val);	//finds all the elements for the given tag
	void first_children(const std::string&tag, sPtr val);	//finds the first children for the given parent tag
	void first_descendents(const std::string&tag, sPtr val);//find all the children for the given parent tag
	sPtr get_attribute_element(const std::string &id, const std::string &value);//finds pointer to the element which has the particular id and value
	sPtr find_attributes(std::string id, std::string value, sPtr temp);//find pointer to the element with the id and value
	bool empty_tree(sPtr value); // check if the tree is empty or not
	bool save(std::string filename); // saving the modification in a new file
	sPtr return_pDoc();
	static std::vector<std::pair<std::string, std::string>> return_attributes(const sPtr &tag);//returns all the attribute for a pointer
	std::string toString(){ return pDocElement_->toString(); }
  private:
    sPtr pDocElement_;         // AST that holds procInstr, comments, XML root, and more comments
    std::vector<sPtr> found_;  // query results
  };
}
#endif
