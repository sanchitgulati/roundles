//
//  LevelXML.cpp
//  OneClosedLoop
//
//  Created by Sanchit Gulati on 23/03/14.
//
//


#include "LevelXML.h"
#include "Util.h"

pugi::xml_document LevelXML::doc;
pugi::xml_node LevelXML::curBundle;
pugi::xml_node LevelXML::curLevel;
int LevelXML::curBundleNumber = 0;
int LevelXML::curLevelNumber = 0;

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

std::string LevelXML::getBundleImageAt(int index)
{
    int localIndex = 0;
    pugi::xml_object_range<pugi::xml_named_node_iterator> itBundle = doc.children("bundle");
    for(pugi::xml_named_node_iterator it=itBundle.begin(); it!=itBundle.end(); it++)
    {
        if(localIndex == index)
            return it->attribute("img").value();
        localIndex++;
    }
    std::ostringstream stringStream;
    stringStream << "No Bundle At Given Index ";
    stringStream << index;
    return stringStream.str();
}

Color3B LevelXML::getBundleColorAt(int index)
{
    int localIndex = 0;
    char delimiter = ',';
    std::string token;
    pugi::xml_object_range<pugi::xml_named_node_iterator> itBundle = doc.children("bundle");
    for(pugi::xml_named_node_iterator it=itBundle.begin(); it!=itBundle.end(); it++)
    {
        if(localIndex == index)
        {
            std::string rgbString = it->attribute("base_color").value();
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

/* To call only after curBundle is set */
int LevelXML::getTotalLevelsInBundle(int index)
{
    if(curBundle == nullptr)
        return -1;
    int returnVal = 0;
    pugi::xml_node level = curBundle.child("level");
    for (; level; level = level.next_sibling())
    {
        returnVal++;
    };
    return returnVal;
}


bool LevelXML::setCurrentBundleId(int index)
{
    if(index <= getTotalBundlesSize())
    {
        int localIndex = 0;
        pugi::xml_object_range<pugi::xml_named_node_iterator> itBundle = doc.children("bundle");
        for(pugi::xml_named_node_iterator it=itBundle.begin(); it!=itBundle.end(); it++)
        {
            if(localIndex == index)
            {
                curBundle = static_cast<pugi::xml_node>(*it);
                LevelXML::curBundleNumber = index;
                return true;
            }
            localIndex++;
        }
    }
    return false;
}

bool LevelXML::setCurrentLevelId(int index)
{
    LevelXML::curLevelNumber = index;
    int localIndex = 0;
    pugi::xml_object_range<pugi::xml_named_node_iterator> itBundle = curBundle.children("level");
    for(pugi::xml_named_node_iterator it=itBundle.begin(); it!=itBundle.end(); it++)
    {
        if(localIndex == index)
        {
            curLevel = static_cast<pugi::xml_node>(*it);
            LevelXML::curLevelNumber = index;
            return true;
        }
        localIndex++;
    }
    return false;
}



std::string LevelXML::getLevelNameAt(int index)
{
    std::string returnVal = "";
    if(curBundle == nullptr)
        return returnVal;
    int localIndex = 0;
    pugi::xml_object_range<pugi::xml_named_node_iterator> itLevel = curBundle.children("level");
    for(pugi::xml_named_node_iterator it=itLevel.begin(); it!=itLevel.end(); it++)
    {
        if(localIndex == index)
        {
            returnVal = it->child("title").text().get();
            
        }
        localIndex++;
    }
    return returnVal;
}

bool LevelXML::getDidCompleteLevelAt(int index)
{
    char key[10];
    sprintf(key, "%d-%d",curBundleNumber,index);
    return cocos2d::UserDefault::getInstance()->getBoolForKey(key, false);
}

bool LevelXML::setLevelCompletedAt(int index)
{
    char key[10];
    sprintf(key, "%d-%d",curBundleNumber,index);
    cocos2d::UserDefault::getInstance()->setBoolForKey(key, true);
    return true;
}

std::vector<LevelElement> LevelXML::getCurrentLevel()
{
    auto vec = std::vector<LevelElement>();
    pugi::xml_object_range<pugi::xml_named_node_iterator> itElement = curLevel.child("data").children("element");
    for(pugi::xml_named_node_iterator it=itElement.begin(); it!=itElement.end(); it++)
    {
        LevelElement temp = LevelElement();
        temp.type = static_cast<eType>(std::atoi(it->attribute("type").value()));
        temp.x = std::atoi(it->attribute("positionX").value());
        temp.y = std::atoi(it->attribute("positionY").value());
        temp.head = -1;
        
        switch (temp.type) {
            case eStart:
                temp.head = std::atoi(it->attribute("head").value());
                break;
            case eTurner:
                temp.metaType = std::atoi(it->attribute("headed").value());
                break;
            case eIce:
                temp.metaType = std::atoi(it->attribute("moves").value());
            default:
                break;
        }
        vec.push_back(temp);
    }
    return vec;
}

std::vector<int> LevelXML::getSolutionLevel()
{
    auto vec = std::vector<int>();
    pugi::xml_node solutionNode = curLevel.child("solution");
    if(std::atoi(solutionNode.attribute("isValid").value())== 0)
        return vec;
    pugi::xml_object_range<pugi::xml_named_node_iterator> itElement = curLevel.child("solution").children("element");
    for(pugi::xml_named_node_iterator it=itElement.begin(); it!=itElement.end(); it++)
    {
        auto value = std::atoi(it->attribute("direction").value());
        vec.push_back(value);
    }
    return vec;
}

int LevelXML::getGridSizeX()
{
    return std::atoi(curLevel.attribute("gridX").value());
}

int LevelXML::getGridSizeY()
{
    return std::atoi(curLevel.attribute("gridY").value());
}

int LevelXML::getLevelId()
{
    return std::atoi(curLevel.attribute("id").value());
}


const char* LevelXML::getLevelImage()
{
    return curBundle.attribute("level_img").value();
}

const char* LevelXML::getLevelIcon()
{
    return curBundle.attribute("icon").value();
}

bool LevelXML::isUnlockedBundleAt(int index)
{
    char key[10];
    sprintf(key, "unlocked-%d",index);
    bool ret = true;//cocos2d::UserDefault::getInstance()->getBoolForKey(key, false);
    return ret;
}

void LevelXML::setBundleUnlockedAt(int index)
{
    char key[10];
    sprintf(key, "unlocked-%d",index);
    cocos2d::UserDefault::getInstance()->setBoolForKey(key, true);
}


int LevelXML::totalLevelsCompletedOfBundleAt(int index)
{
    char key[10];
    int ret = 0;
    for(int i =0;i < getTotalLevelsInBundle(index);i++)
    {
        sprintf(key, "%d-%d",index,i);
        auto val = cocos2d::UserDefault::getInstance()->getBoolForKey(key, false);
        if(val)
            ret++;
    }
    return ret;
}

