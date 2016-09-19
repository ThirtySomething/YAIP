/**
 * \file	YAIP++Data.h
 * \author	ThirtySomething
 * \date	2016-09-19
 * \brief	Basic definitions for YAIP++
 */
#pragma once

#include <map>
#include <memory>
#include <regex>
#include <string>
#include <vector>

/**
 * Namespace of YAIP
 */
namespace YAIP
{
	/**
	 * This struct will be passed to each map and will ensure an alphabetical order of all keys
	 */
	struct StringCompareCaseLess : std::binary_function<std::string, std::string, bool>
	{
		/**
		 * Comparison of two strings represented by unsigned chars
		 */
		struct CompareCaseless : public std::binary_function<unsigned char, unsigned char, bool>
		{
			/**
			 * Operator for usage in string compare
			 * \param c1 Left string to check
			 * \param c2 Right string to check
			 * \return true in case the left string is less than the right string
			 */
			bool operator() (const unsigned char& c1, const unsigned char& c2) const
			{
				return tolower(c1) < tolower(c2);
			}
		};

		/**
		 * Operator for usage in string compare
		 * \param s1 Left string to check
		 * \param s2 Right string to check
		 * \return true in case the left string is less than the right string
		 */
		bool operator() (const std::string & s1, const std::string & s2) const
		{
			return std::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), CompareCaseless());
		}
	};

	/**
	 * Convenience typedef for a vector of strings.
	 * Used to represent the content of a INI file, a list of sections or a list of keys.
	 */
	typedef std::vector<std::string> tVectorString;

	/**
	 * Convenience typedef for a map of strings.
	 * Used to represent keys and their corresponding values.
	 * Map will be sorted caseless.
	 */
	typedef std::map<std::string, std::string, StringCompareCaseLess> tMapStringString;

	/**
	 * Convenience typedef for a map of strings.
	 * Used to represent a section with their corrresponding keys/value storage.
	 * Map will be sorted caseless.
	 */
	typedef std::map<std::string, tMapStringString, StringCompareCaseLess> tMapMapStringString;
}
