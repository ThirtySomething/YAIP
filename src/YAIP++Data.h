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
			 * \param StringLeft Left string to check
			 * \param StringRight Right string to check
			 * \return true in case the left string is less than the right string
			 */
			bool operator() (const unsigned char& StringLeft, const unsigned char& StringRight) const
			{
				return tolower(StringLeft) < tolower(StringRight);
			}
		};

		/**
		 * Operator for usage in string compare
		 * \param StringLeft Left string to check
		 * \param StringRight Right string to check
		 * \return true in case the left string is less than the right string
		 */
		bool operator() (const std::string & StringLeft, const std::string & StringRight) const
		{
			return std::lexicographical_compare(StringLeft.begin(), StringLeft.end(), StringRight.begin(), StringRight.end(), CompareCaseless());
		}
	};

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

	/**
	 * Convenience typedef for a vector of strings.
	 * Used to represent the content of a INI file, a list of sections or a list of keys.
	 */
	typedef std::vector<std::string> tVectorString;
}
