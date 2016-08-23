// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <string>
#include <vector>
#include "Types.h"
#include "SearchResultModel.h"
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            namespace
            {
                std::string ExtractAnyVersion4Data(rapidjson::Document& document)
                {
                    rapidjson::Document jsonDoc;
                    rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();
                    rapidjson::Value valueObject(rapidjson::kObjectType);
                    std::string jsonString ="";
                    
                    if(document.HasMember("phone") && std::string(document["phone"].GetString()).empty() == false)
                    {
                        valueObject.AddMember("display_phone", rapidjson::Value(document["display_phone"], allocator).Move(), allocator);
                    }
                    if(document.HasMember("web") && std::string(document["web"].GetString()).empty() == false)
                    {
                        valueObject.AddMember("url", rapidjson::Value(document["web"], allocator).Move(), allocator);
                    }
                    if(document.HasMember("imageUrl") && std::string(document["imageUrl"].GetString()).empty() == false)
                    {
                        valueObject.AddMember("image_url", rapidjson::Value(document["imageUrl"], allocator).Move(), allocator);
                    }
                    if(document.HasMember("ratingImageUrl") && std::string(document["ratingImageUrl"].GetString()).empty() == false)
                    {
                        valueObject.AddMember("rating", rapidjson::Value(document["ratingImageUrl"], allocator).Move(), allocator);
                    }
                    if(document.HasMember("reviews"))
                    {
                        const rapidjson::Value& reviewsJson(document["reviews"]);
                        if(reviewsJson.Size() > 0)
                        {
                            rapidjson::SizeType index = 0;
                            valueObject.AddMember("snippet_text", rapidjson::Value(reviewsJson[index], allocator).Move(), allocator);
                        }
                    }
                    if(document.HasMember("reviewCount"))
                    {
                        valueObject.AddMember("review_count", document["reviewCount"].GetInt(), allocator);
                    }
                    
                    rapidjson::StringBuffer strbuf;
                    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
                    valueObject.Accept(writer);
                    return strbuf.GetString();
                }
            }
            std::string SerializeToJson(const SearchResultModel& searchResult)
            {
                Eegeo_ASSERT(false, "TODO: tags. Not supported. Todo: deprecate nicely");

                rapidjson::Document jsonDoc;
                rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();
                rapidjson::Value valueObject(rapidjson::kObjectType);
                
                rapidjson::Value categoriesJson(rapidjson::kArrayType);
                const std::vector<std::string>& categories(searchResult.GetHumanReadableTags());
                for(std::vector<std::string>::const_iterator it = categories.begin(); it != categories.end(); ++ it)
                {
                    categoriesJson.PushBack(rapidjson::Value(it->c_str(), allocator).Move(), allocator);
                }
                
                valueObject.AddMember("version", searchResult.GetVersion(), allocator);
                valueObject.AddMember("id", rapidjson::Value(searchResult.GetIdentifier().c_str(), allocator).Move(), allocator);
                valueObject.AddMember("title", rapidjson::Value(searchResult.GetTitle().c_str(), allocator).Move(), allocator);
                valueObject.AddMember("subtitle", rapidjson::Value(searchResult.GetSubtitle().c_str(), allocator).Move(), allocator);
                valueObject.AddMember("interior", searchResult.IsInterior(), allocator);
                valueObject.AddMember("building", rapidjson::Value(searchResult.GetBuildingId().Value().c_str(), allocator).Move(), allocator);
                valueObject.AddMember("floor", searchResult.GetFloor(), allocator);

                // TODO tags: figure out what to do with this
                //valueObject.AddMember("category", rapidjson::Value(searchResult.GetCategory().c_str(), allocator).Move(), allocator);
                valueObject.AddMember("humanReadableCategories", categoriesJson, allocator);
                valueObject.AddMember("vendor", rapidjson::Value(searchResult.GetVendor().c_str(), allocator).Move(), allocator);
                valueObject.AddMember("latitude", searchResult.GetLocation().GetLatitudeInDegrees(), allocator);
                valueObject.AddMember("longitude", searchResult.GetLocation().GetLongitudeInDegrees(), allocator);
                valueObject.AddMember("heightAboveTerrain", searchResult.GetHeightAboveTerrainMetres(), allocator);
                valueObject.AddMember("json", rapidjson::Value(searchResult.GetJsonData().c_str(), allocator).Move(), allocator);
                valueObject.AddMember("createTimestamp", searchResult.GetCreationTimestamp(), allocator);
                
                rapidjson::StringBuffer strbuf;
                rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
                valueObject.Accept(writer);
                return strbuf.GetString();
                
            }
            
            bool TryDeserializeFromJson(const std::string& searchResultJson, SearchResultModel& out_resultModel)
            {
                Eegeo_ASSERT(false, "TODO: tags. Not supported. Deprecate nicely");

                rapidjson::Document document;
                
                const bool successfullyParsed = !(document.Parse<0>(searchResultJson.c_str()).HasParseError());
                
                if(!successfullyParsed)
                {
                    Eegeo_TTY("Failed to parse search result model JSON.\n");
                    return false;
                }
                
                if(!document.HasMember("version"))
                {
                    Eegeo_TTY("Old SearchResultModel version detected. Please delete and reinstall the application.\n");
                    return false;
                }
                
                int version = document["version"].GetInt();
                
                const int earliestSupportedVersionForUpversioning = 4;
                
                if(version < earliestSupportedVersionForUpversioning)
                {
                    Eegeo_TTY("Old SearchResultModel version detected: tried to deserialize version %d but current version is %d. Please delete and reinstall the application.\n", version, SearchResultModel::CurrentVersion);
                    return false;
                }
                
                std::string jsonData = "";
                if(version == 4)
                {
                    jsonData = ExtractAnyVersion4Data(document);
                    version = SearchResultModel::CurrentVersion;
                }
                else if(version > 4)
                {
                    jsonData = document["json"].GetString();
                }
                
                const rapidjson::Value& categoriesJson(document["humanReadableCategories"]);
                std::vector<std::string> categories;
                for(rapidjson::SizeType i = 0; i < categoriesJson.Size(); ++ i)
                {
                    categories.push_back(categoriesJson[i].GetString());
                }
                
                bool interior = false;
                if(document.HasMember("interior"))
                {
                    interior = document["interior"].GetBool();
                }
                
                std::string building = "";
                if(document.HasMember("building"))
                {
                    building = document["building"].GetString();
                }
        
                int floor = 0;
                if(document.HasMember("floor"))
                {
                    floor = document["floor"].GetInt();
                }
                
                float heightAboveTerrainMetres = 0;
                if(document.HasMember("heightAboveTerrain"))
                {
                    heightAboveTerrainMetres = static_cast<float>(document["heightAboveTerrain"].GetDouble());
                }

                // TODO: tags ...
                Search::SdkModel::TagIconKey tagIconKey = document["category"].GetString();
                std::vector<std::string> tags;

                out_resultModel = SearchResultModel(version,
                                                    document["id"].GetString(),
                                                    document["title"].GetString(),
                                                    document.HasMember("address") ? document["address"].GetString() : document["subtitle"].GetString(),
                                                    Eegeo::Space::LatLong::FromDegrees(document["latitude"].GetDouble(),
                                                                                       document["longitude"].GetDouble()),
                                                    heightAboveTerrainMetres,
                                                    interior,
                                                    building,
                                                    floor,                                                    
                                                    categories,
                                                    tags,
                                                    tagIconKey,
                                                    document["vendor"].GetString(),
                                                    jsonData,
                                                    document["createTimestamp"].GetInt64());
                
                return true;
            }
        }
    }
}
