#include "Json.h"
#include "EFile.h"
#include "Math/Vector2.h"
#include "Math/Color.h"

#include <rapidjson/istreamwrapper.h>
#include <iostream>

namespace Json
{
    bool Load(const std::string& filename, rapidjson::Document& document)
    {
        // read the file into a string
        std::string buffer;
        if (!File::ReadFile(filename, buffer))
        {
            return false;
        }

        // convert the string into a json stream
        std::stringstream stream(buffer);
        rapidjson::IStreamWrapper istream(stream);

        // set the json document from the stream
        document.ParseStream(istream);
        // check if the parse was successful
        if (!document.IsObject())
        {
            std::cerr << "Could not parse Json: " << filename << std::endl;
            return false;
        }

        return true;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, int& data)
    {
        // check if the value has the "<name>" and the correct data type
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsInt())
        {
            std::cerr << "Could not read Json value: " << name << std::endl;
            return false;
        }

        // get the data
        data = value[name.c_str()].GetInt();

        return true;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, float& data)
    {
        // check if the value has the "<name>" and the correct data type
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsNumber())
        {
            std::cerr << "Could not read Json value: " << name << std::endl;
            return false;
        }

        // get the data
        data = value[name.c_str()].GetFloat();

        return true;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, bool& data)
    {
        // check if the value has the "<name>" and the correct data type
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsBool())
        {
            std::cerr << "Could not read Json value: " << name << std::endl;
            return false;
        }

        // get the data
        data = value[name.c_str()].GetBool();

        return true;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, std::string& data)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsString())
        {
            std::cerr << "Could not read Json value: " << name << std::endl;
            return false;
        }

        data = value[name.c_str()].GetString();

        return true;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, Vector2& data)
    {
        // check if the value has the "<name>" and is an array with 2 elements
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 2)
        {
            std::cerr << "Could not read Json value: " << name << std::endl;
            return false;
        }

        // get json array object
        auto& array = value[name.c_str()];
        // get array values
        for (rapidjson::SizeType i = 0; i < array.Size(); i++)
        {
            if (!array[i].IsNumber())
            {
                std::cerr << "Could not read Json value: " << name << std::endl;
                return false;
            }

            // get the data
            data[i] = array[i].GetFloat();
        }

        return true;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, Color& data)
    {
        // check if the value has the "<name>" and is an array with 4 elements
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 4)
        {
            std::cerr << "Could not read Json value: " << name << std::endl;
            return false;
        }

        // get json array object
        auto& array = value[name.c_str()];
        // get array values
        for (rapidjson::SizeType i = 0; i < array.Size(); i++)
        {
            if (!array[i].IsNumber())
            {
                std::cerr << "Could not read Json value: " << name << std::endl;
                return false;
            }

            // get the data
            data[i] = array[i].GetFloat();
        }

        return true;
    }
}
