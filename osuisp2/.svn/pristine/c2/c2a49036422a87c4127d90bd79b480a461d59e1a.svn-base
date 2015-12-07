
#include "..\include\Config.h"


using namespace rapidxml;
using namespace std;

	Config::Config()
	{
		this->errStrings = "";
		this->LoadConfiguration();
		this->LoadProgrammers();
		this->LoadModels();
		this->LoadOptionsNode();
	}

	void Config::Persist ()
	{
		// Remove all parts and programmers from the document
		partsNode->remove_all_nodes();
		programmersNode->remove_all_nodes();
		
		for (size_t i = 0; i<parts.size(); i++)
		{
			this->AddSupportedModel(parts[i]);
		}
		for (size_t i = 0; i<programmers.size(); i++)
		{
			this->AddProgrammer(programmers[i]);
		}
		
		// Load document into a string
		string s;
		print(std::back_inserter(s), doc, 0);
		
		// Write the string to the config file
		ofstream file;
		file.open (CONFIG_FILE);
		file << s;
		file.close();
	}
	
	// Returns 0 if the strings are the same
	// or 1 if they are different.
	int Config::StrCmp(string s, string t)
	{
		if (s.length()!=t.length())
			return 1;
		
		for (size_t i= 0; i<s.length(); i++)
		{
			if (toupper(s[i])!=toupper(t[i]))
				return 1;
		}
		return 0;
	}
	
	int Config::GetPartByName (string partName, Part *part)
	{
		size_t i = 0;
		for (i = 0; i < parts.size(); i++)
		{
			if (this->StrCmp(parts[i].name, partName)==0)
				break;
		}
		if (i < parts.size())
		{
			*part = parts[i];
			return 0;
		}
		return -1;
	}
	
	int Config::GetProgrammerByName (string progName, Programmer *prog)
	{
		size_t i = 0;
		for (i = 0; i < programmers.size(); i++)
		{
			if (StrCmp(programmers[i].name, progName)==0)
				break;
		}
		if (i < programmers.size())
		{
			*prog = programmers[i];
			return 0;
		}
		return -1;
	}
	
	void Config::LoadProgrammers()
	{
		programmers.clear();
		for (xml_node<> *node = programmersNode->first_node("supported-programmer");
			node!=NULL; node = node->next_sibling("supported-programmer"))
		{
			Programmer p;
			xml_attribute<> * att = node->first_attribute("name");
			if (att!=NULL) p.name = att->value();
			att = node->first_attribute("isCommon");
			if (att!=NULL) p.isCommon = att->value();
			
			this->LoadProgrammerParams(node, &p);
			
			programmers.push_back(p);
		}
	}
	
	void Config::LoadProgrammerParams(xml_node<>*node, Programmer * p)
	{
		vector<Param> params;
		xml_attribute<>* att;
		
		// Loop through param nodes
		for (xml_node<> * paramNode = node->first_node("param");
			paramNode!=NULL; paramNode = paramNode->next_sibling("param"))
		{
			Param param;
			att = paramNode->first_attribute("name");
			if (att!=NULL) param.name = att->value();
			
			att = paramNode->first_attribute("flag");
			if (att!=NULL) param.flag = att->value();
			
			att = paramNode->first_attribute("canEdit");
			if (att!=NULL) param.canEdit = att->value();
			
			att = paramNode->first_attribute("defaultIndex");
			if (att!=NULL) param.defaultIndex = atoi(att->value());
			else param.defaultIndex = 0;
			
			att = paramNode->first_attribute("values");
			if (att!=NULL) param.values = Split (att->value(), ", ");
			
			params.push_back(param);
		}
		
		p->params = params;
	}
	
	// TODO: Adds programmer params from the programmer to the node
	void Config::AddProgrammerParams(xml_node<>*node, Programmer * p)
	{
	}
	
	void Config::LoadModels ()
	{
		parts.clear();
		for (xml_node<>* node = partsNode->first_node("supported-part");
			node!=NULL; node = node->next_sibling("supported-part"))
		{
			// Description Data
			Part m;
			xml_attribute<> *att = node->first_attribute("name");
			if (att!=NULL) m.name = att->value();
			
			att = node->first_attribute("id");
			if (att!=NULL) m.id = att->value();
			
			att = node->first_attribute("abbreviation");
			if (att!=NULL) m.abbreviation = att->value();
			
			m.fuse = this->LoadFuseData(node, "fuse");
			m.lfuse= this->LoadFuseData(node, "lfuse");
			m.hfuse= this->LoadFuseData(node, "hfuse");
			m.efuse= this->LoadFuseData(node, "efuse");
			m.lock = this->LoadFuseData(node, "lock");

			parts.push_back(m);
		}
	}
	
	void Config::AddProgrammer (struct Programmer &programmer)
	{
		if (programmersNode!=NULL)
		{
			xml_node<> * supportedProgrammerNode = doc.allocate_node(node_element, doc.allocate_string("supported-programmer"));
			
			xml_attribute<> *attr = doc.allocate_attribute("name", doc.allocate_string(programmer.name.c_str()));
			supportedProgrammerNode->append_attribute(attr);
			
			attr = doc.allocate_attribute("isCommon", doc.allocate_string(programmer.isCommon.c_str()));
			supportedProgrammerNode->append_attribute(attr);
			
			programmersNode->append_node(supportedProgrammerNode);
		}
	}
	
	void Config::AddSupportedModel(struct Part &model)
	{	
		if (partsNode!=NULL)
		{
			char * node_name = doc.allocate_string("supported-part");        // Allocate string and copy name into it
			xml_node<> *supportedModelNode = doc.allocate_node(node_element, node_name);  // Set node name to node_name
			
			xml_attribute<> *attr = doc.allocate_attribute("name", doc.allocate_string(model.name.c_str()));
			supportedModelNode->append_attribute(attr);
			
			attr = doc.allocate_attribute("id", doc.allocate_string(model.id.c_str()));
			supportedModelNode->append_attribute(attr);
			attr = doc.allocate_attribute("abbreviation", doc.allocate_string(model.abbreviation.c_str()));
			supportedModelNode->append_attribute(attr);
			
			this->AddFuseData(supportedModelNode, "fuse", model.fuse);
			this->AddFuseData(supportedModelNode, "lfuse", model.lfuse);
			this->AddFuseData(supportedModelNode, "hfuse", model.hfuse);
			this->AddFuseData(supportedModelNode, "efuse", model.efuse);
			this->AddFuseData(supportedModelNode, "lock", model.lock);
		
			partsNode->append_node(supportedModelNode);
		}
	}
	
	void Config::LoadConfiguration()
	{
		// Load default configuration
		ifstream  file (CONFIG_FILE);
		string s = "";
		if (file.is_open())
		{
			while (!file.eof())
			{
				string line = "";
				getline (file, line);
				s.append(line);
			}
			file.close();
		}
		else
		{
			errStrings.append("Could not open file ");
			errStrings.append(CONFIG_FILE);
			errStrings.append("\n");
		}
		
		this->ParseStringToDocument(s);
		this->VerifyRootNode();
		this->VerifyPartsNode();
		this->VerifyProgrammersNode();
		//this->VerifyDefaultProgrammerNode();
	}
	
	void Config::ParseStringToDocument(string s)
	{
		// Parse the config file
		try
		{
			doc.parse<0>(doc.allocate_string(s.c_str()));
		}
		catch (parse_error p)
		{
			doc.clear();
			errStrings.append("Error parsing file ");
			errStrings.append(CONFIG_FILE);
			errStrings.append(": ");
			errStrings.append(p.what());
			errStrings.append("\n");
		}
		catch (...)
		{
			doc.clear();
			errStrings.append("Error parsing file ");
			errStrings.append(CONFIG_FILE);
			errStrings.append("\n");
		}
	}
	
	void Config::LoadOptionsNode()
	{
		options.flash = false;
		options.eeprom = false;
		options.fuseBits = false;
		options.lockBits = false;	
		
		xml_node<>* optionsNode = root->first_node("avr-options");
		if (optionsNode!=NULL)
		{
			options.flash = GetEnabledAttributeValue(optionsNode->first_node("program-flash"));
			options.eeprom= GetEnabledAttributeValue(optionsNode->first_node("program-eeprom"));
			options.fuseBits=GetEnabledAttributeValue(optionsNode->first_node("program-fuse-bits"));
			options.lockBits=GetEnabledAttributeValue(optionsNode->first_node("program-lock-bits"));
		}
	}
	
	bool Config::GetEnabledAttributeValue(xml_node<>* node)
	{
		if (node != NULL)
		{
			xml_attribute <>* enabled = node->first_attribute("enabled");
			if (enabled != NULL)
			{
				return StrCmp(enabled->value(), "true") == 0;
			}
		}
		return false;
	}
	
	void Config::VerifyRootNode()
	{
		// Locate Root node:
		root = doc.first_node("Universal-GUI-Config");
		if (root==NULL) // If no root node is found, create a new temporary document with an empty configuration
		{
			doc.clear();
			root = doc.allocate_node(node_element, doc.allocate_string("Universal-GUI-Config"));  // Set node name to node_name
			doc.append_node(root);
			errStrings.append("Node 'Config' was not found in file ");
			errStrings.append(CONFIG_FILE);
			errStrings.append("\n");
		}
	}
	
	void Config::VerifyPartsNode()
	{
		// Locate Supported Models node:
		partsNode = root->first_node("supported-parts");
		if (partsNode==NULL) // If not found, create
		{
			partsNode = doc.allocate_node(node_element, doc.allocate_string("supported-parts"));
			root->append_node(partsNode);
			errStrings.append("Child node 'supported-parts' was not found in file ");
			errStrings.append(CONFIG_FILE);
			errStrings.append("\n");
		}
	}
	
	void Config::VerifyProgrammersNode()
	{
		// Locate Supported Programmers node:
		programmersNode = root->first_node("supported-programmers");
		if (programmersNode==NULL) // If not found, create
		{
			programmersNode = doc.allocate_node(node_element, doc.allocate_string("supported-programmers"));
			root->append_node(programmersNode);
			errStrings.append("Child node 'supported-programmers' was not found in file ");
			errStrings.append(CONFIG_FILE);
			errStrings.append("\n");
		}
	}

void Config::AddFuseData (xml_node<> *parentNode, string name, vector<string> names)
{
	// No need to persist empty data.
	if (names.size()==0)
		return;
		
	xml_node<> * fuseNode = doc.allocate_node(node_element, doc.allocate_string(name.c_str()));
	parentNode->append_node(fuseNode);
	
	string s = "";
	for (size_t i = 0; i<names.size(); i++)
	{
		s.append(names[i]);
		if ((i+1)<names.size()) s.append(", ");
	}
	xml_attribute<> * att = doc.allocate_attribute("names", doc.allocate_string(s.c_str()));
	fuseNode->append_attribute(att);
}	

vector<string> Config::LoadFuseData(xml_node<> * node, const char * name)
{
	vector<string> strings;
	
	xml_node<> * fuseNode = node->first_node(name);
	if (fuseNode!=NULL)
	{
		xml_attribute<> * att = fuseNode->first_attribute("names");
		if (att!=NULL)
		{
			strings = Split (att->value(), ", ");
		}
	}
	return strings;
}
	
vector<string> Config::Split(string strToSplit, string splitChars)
{
    vector<string> strings;
    size_t lastIndex = 0, index = 0;
    
    do
    {
        index = strToSplit.find_first_of(splitChars, lastIndex);

        // Skip sequential split chars (prevents empty results)
        if (index!=lastIndex)
            strings.push_back (strToSplit.substr(lastIndex, index-lastIndex));

        lastIndex = index + 1;
    }
    while (index != string::npos && lastIndex != strToSplit.size());

    return strings;
}


