#ifndef STAN__INTERFACE_CALLBACKS__WRITER__BASE_WRITER_HPP
#define STAN__INTERFACE_CALLBACKS__WRITER__BASE_WRITER_HPP

#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>

namespace stan {
  namespace interface_callbacks {
    namespace writer {
      
      class base_writer {
      public:
        virtual ~base_writer() {};
        
        virtual void write_key_value(const std::string& key,
                                     double value) = 0;
        virtual void write_key_value(const std::string& key,
                                     const std::string& value) = 0;
        
        virtual void write_state_names(std::vector<std::string>& names) = 0;
        virtual void write_state(std::vector<double>& state) = 0;
        
        virtual void write_message() = 0;
        virtual void write_message(const std::string& message) = 0;
        
      };

    }
  }
}

#endif
