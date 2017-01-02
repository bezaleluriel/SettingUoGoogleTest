#ifndef EX1_MARITALSTATUS_H
#define EX1_MARITALSTATUS_H
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/access.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/archive/tmpdir.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>

/**
 * enum class for maitalstatus options.
 */

enum class MaritalStatus{
    Single, Married, Divorced , Widowed
};

namespace boost
{
    namespace serialization
    {

        template< class Archive >
        void save(Archive & ar, const MaritalStatus & t, unsigned int version)
        {
            unsigned char c = (unsigned char) t;
            ar & c;
        }

        template< class Archive >
        void load(Archive & ar, MaritalStatus & t, unsigned int version)
        {
            unsigned char c;
            ar & c;
            t = (MaritalStatus) c;
        }

    } // namespace serialization
} // namespace boost

BOOST_SERIALIZATION_SPLIT_FREE(MaritalStatus)

#endif //EX1_MARITALSTATUS_H
