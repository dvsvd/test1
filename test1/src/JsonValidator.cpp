#include "JsonValidator.h"
#include "Functions.h"

JsonValidator::JsonValidator(const json& schema)
	: m_schema(schema)
{
	initialize_map();
}

JsonValidator::JsonValidator(const std::string& raw_schema)
	: m_schema(json::parse(raw_schema))
{
	initialize_map();
}

void JsonValidator::initialize_map()
{
#define hash Functions::fnv1a
	m_map.clear();
	for (auto it = m_schema.cbegin(); it != m_schema.cend(); it++)
	{
		if (m_map.count(it.key()) != 0)
			throw std::logic_error("Specified key already exists in schema");
		switch (hash(it.value().get<json::string_t>().c_str()))
		{
		case hash("string"):
			m_map[it.key()] = json::value_t::string;
			break;
		case hash("array"):
			m_map[it.key()] = json::value_t::array;
			break;
		case hash("object"):
			m_map[it.key()] = json::value_t::object;
			break;
		case hash("float"):
			m_map[it.key()] = json::value_t::number_float;
			break;
		case hash("int"):
			m_map[it.key()] = json::value_t::number_integer;
			break;
		case hash("bool"):
			m_map[it.key()] = json::value_t::boolean;
			break;
		case hash("null"):
			m_map[it.key()] = json::value_t::null;
			break;
		default:
			throw std::logic_error("Invalid type specifier");
		}
	}
#undef hash
}

bool JsonValidator::validate(const json& data) const
{
	size_t count = 0;
	bool ret = data.size() == m_schema.size();
	for (auto it = data.cbegin(); it != data.cend() && ret; it++)
	{
		// Get value type from m_map of the according key
		// Avoid exception handling of at()
		auto e = m_map.find(it.key());
		ret = e != m_map.end() && it.value().type() == e->second;
	}
	return ret;
}