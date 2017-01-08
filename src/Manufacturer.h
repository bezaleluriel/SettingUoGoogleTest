//#ifndef EX1_MANUFACTURER_H
//#define EX1_MANUFACTURER_H
//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>
//#include <boost/serialization/access.hpp>
//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>
//#include <boost/tokenizer.hpp>
//#include <boost/algorithm/string/predicate.hpp>
//#include <boost/lexical_cast.hpp>
//#include <boost/assign/list_of.hpp>
//#include <boost/algorithm/string.hpp>
//#include <boost/iostreams/device/back_inserter.hpp>
//#include <boost/iostreams/stream.hpp>
//#include <boost/archive/binary_oarchive.hpp>
//#include <boost/archive/binary_iarchive.hpp>
//#include <boost/archive/binary_iarchive.hpp>
//#include <boost/serialization/base_object.hpp>
//#include <boost/archive/tmpdir.hpp>
//#include <boost/archive/text_iarchive.hpp>
//#include <boost/archive/text_oarchive.hpp>
//#include <boost/serialization/base_object.hpp>
//#include <boost/serialization/utility.hpp>
//#include <boost/serialization/list.hpp>
//#include <boost/serialization/assume_abstract.hpp>
//#include <boost/serialization/export.hpp>
//
///**
// * enum class for types of car manufacturers.
// */
//namespace std {
//    enum class Manufacturer {
//        Honda, Subaro, Tesla, Fiat
//    };
//}
////namespace boost
////{
////    namespace serialization
////    {
////
////        template< class Archive >
////        void save(Archive & ar, const Manufacturer & t, unsigned int version)
////        {
////            unsigned char c = (unsigned char) t;
////            ar & c;
////        }
////
////        template< class Archive >
////        void load(Archive & ar, Manufacturer & t, unsigned int version)
////        {
////            unsigned char c;
////            ar & c;
////            t = (Manufacturer) c;
////        }
////
////    } // namespace serialization
////} // namespace boost
//
////BOOST_SERIALIZATION_SPLIT_FREE(Manufacturer)
//
//#endif //EX1_MANUFACTURER_H