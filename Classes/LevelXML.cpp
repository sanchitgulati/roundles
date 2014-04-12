//
//  LevelXML.cpp
//  OneClosedLoop
//
//  Created by Sanchit Gulati on 23/03/14.
//
//


#include "LevelXML.h"


pugi::xml_document LevelXML::doc;

bool LevelXML::init()
{
    
	FileUtils *sharedFileUtils = FileUtils::getInstance();
    Data data = sharedFileUtils->getDataFromFile("levels.xml");
    
    unsigned char* pBuffer = data.getBytes();
    unsigned long nSize = data.getSize();
    
    if (!doc.load_buffer(pBuffer, nSize))
        return false;
    
    return true;
}



void LevelXML::traverse()
{
    pugi::xml_node levels = doc.child("bundle");
    
    log("Bundle");
    
    //[code_traverse_base_basic
    for (pugi::xml_node level = levels.first_child(); level; level = level.next_sibling())
    {
        
        log("Level");
        
        for (pugi::xml_attribute attr = level.first_attribute(); attr; attr = attr.next_attribute())
        {
            log(" Name %s Value %s ",attr.name(),attr.value());
            for (pugi::xml_attribute attr = level.first_attribute(); attr; attr = attr.next_attribute())
            {
                log(" Name %s Value %s ",attr.name(),attr.value());
            }
        }
    }
}


int LevelXML::getTotalBundlesSize()
{
    int returnVal = 0;
    pugi::xml_node bundle = doc.child("bundle");
    for (; bundle; bundle = bundle.next_sibling())
    { returnVal++;};
    return returnVal;
}


std::string LevelXML::getBundleNameAt(int index)
{
    int localIndex = 0;
    pugi::xml_object_range<pugi::xml_named_node_iterator> itBundle = doc.children("bundle");
    for(pugi::xml_named_node_iterator it=itBundle.begin(); it!=itBundle.end(); it++)
    {
        if(localIndex == index)
            return it->attribute("value").value();
        localIndex++;
    }
    std::ostringstream stringStream;
    stringStream << "No Bundle At Given Index ";
    stringStream << index;
    return stringStream.str();
}

Color3B LevelXML::getBundleColorInnerAt(int index)
{
    int localIndex = 0;
    char delimiter = ',';
    std::string token;
    pugi::xml_object_range<pugi::xml_named_node_iterator> itBundle = doc.children("bundle");
    for(pugi::xml_named_node_iterator it=itBundle.begin(); it!=itBundle.end(); it++)
    {
        if(localIndex == index)
        {
            std::string rgbString = it->attribute("rgb_inner").value();
            std::istringstream iString(rgbString);
            Color3B newColor = Color3B();
            newColor = Color3B::BLACK;
            for(int i =0;std::getline(iString, token, delimiter);i++)
            {
                switch (i) {
                    case 0:
                        newColor.r = std::atoi(token.c_str());
                        break;
                    case 1:
                        newColor.g = std::atoi(token.c_str());
                        break;
                    case 2:
                        newColor.b = std::atoi(token.c_str());
                        break;
                        
                    default:
                        break;
                }
            }
            return newColor;
        }
        localIndex++;
    }
    return Color3B::BLACK;
}

Color3B LevelXML::getBundleColorOuterAt(int index)
{
    int localIndex = 0;
    char delimiter = ',';
    std::string token;
    pugi::xml_object_range<pugi::xml_named_node_iterator> itBundle = doc.children("bundle");
    for(pugi::xml_named_node_iterator it=itBundle.begin(); it!=itBundle.end(); it++)
    {
        if(localIndex == index)
        {
            std::string rgbString = it->attribute("rgb_outer").value();
            std::istringstream iString(rgbString);
            Color3B newColor = Color3B();
            newColor = Color3B::BLACK;
            for(int i =0;std::getline(iString, token, delimiter);i++)
            {
                switch (i) {
                    case 0:
                        newColor.r = std::atoi(token.c_str());
                        break;
                    case 1:
                        newColor.g = std::atoi(token.c_str());
                        break;
                    case 2:
                        newColor.b = std::atoi(token.c_str());
                        break;
                        
                    default:
                        break;
                }
            }
            return newColor;
        }
        localIndex++;
    }
    return Color3B::BLACK;
}