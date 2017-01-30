/**
 * \file	YAIP++Data.h
 * \author	ThirtySomething
 * \date	2016-09-19
 * \brief	Basic definitions for YAIP++
 */
#pragma once

#include <functional>
#include <locale>
#include <map>
#include <vector>
#include <string>
#include <ctype.h>

 /**
  * Namespace of YAIP
  */
namespace org
{
	/**
	 * Namespace of YAIP
	 */
	namespace derpaul
	{
		/**
		 * Namespace of YAIP
		 */
		namespace yaip
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
					 * \param CharLeft Left character to check
					 * \param CharRight Right character to check
					 * \return true in case the left character is less than the right character
					 */
					bool operator() (const unsigned char& CharLeft, const unsigned char& CharRight) const
					{
						return (tolower(CharLeft) < tolower(CharRight));
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
			 * Convenience typedef for a map of keys/values.
			 * Used to represent a section with their corrresponding keys/values storage.
			 * Map will be sorted caseless.
			 */
			typedef std::map<std::string, tMapStringString, StringCompareCaseLess> tMapStringMapStringString;

			/**
			 * Convenience typedef for a vector of strings.
			 * Used to represent the content of a INI file, a list of sections or a list of keys.
			 */
			typedef std::vector<std::string> tVectorString;
		}
	}
}
