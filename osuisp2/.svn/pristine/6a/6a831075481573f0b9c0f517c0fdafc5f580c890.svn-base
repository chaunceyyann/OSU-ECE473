

#ifndef _CONFIG_H
#define _CONFIG_H

#define CONFIG_FILE "UGUIConfig.xml"

#include "../rapidXml/rapidxml.hpp"
#include "../rapidXml/rapidxml_print.hpp"
#include "../rapidXml/rapidxml_utils.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>







using namespace rapidxml;
using namespace std;


struct Options
{
	bool flash;
	bool eeprom;
	bool fuseBits;
	bool lockBits;
};

struct Param
{
	string name;
	string flag;
	string canEdit; // true or false, lower case
	int defaultIndex;
	vector<string> values;
};

struct Programmer
{
	string name;
	string isCommon; // yes or no, lower case
	vector<Param> params; // Can have many params (like -P usb)
};

struct Part
{
	string name;
	string id;
	string abbreviation;
	vector<string> fuse;
	vector<string> lfuse;
	vector<string> hfuse;
	vector<string> efuse;
	vector<string> lock;
};

class Config
{
	public:
	
	string errStrings;
	xml_node<> * partsNode;
	xml_node<> * programmersNode;
	vector<Part> parts;
	vector<Programmer> programmers;
	Options options;
	
	Config();

	void Persist ();
	int StrCmp(string s, string t);
	int GetPartByName (string partName, Part *part);
	int GetProgrammerByName (string progName, Programmer *prog);
	
	private:
	
	xml_document<> doc;
	xml_node<> * root;
	
	
	void LoadModels ();
	
	
	void AddSupportedModel(struct Part &model);
	void LoadConfiguration();
	void ParseStringToDocument(string s);
	void VerifyRootNode();
	void VerifyPartsNode();
	void VerifyProgrammersNode();
	
	// Options node items
	void LoadOptionsNode();
	bool GetEnabledAttributeValue(xml_node<>* node);
	
	
	void LoadProgrammers();
	void AddProgrammer (struct Programmer &programmer);
	void LoadProgrammerParams(xml_node<>*node, Programmer * p);
	void AddProgrammerParams(xml_node<>*node, Programmer * p);
	
	void AddFuseData (xml_node<> *parentNode, string name, vector<string> names);

	vector<string> LoadFuseData(xml_node<> * node, const char * name);
	
	/** Split a string into a vector of strings.
	 All split characters are trimmed from the start
	 and end of the resulting strings.  No empty
	 strings are returned.
	 @param strToSplit the input string to split
	 @param splitChars string with chars to base split on
	 @return vector<string> containing the split strings
	*/
	vector<string> Split(string strToSplit, string splitChars);

};











#endif
