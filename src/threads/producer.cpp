#include <iostream>

#include "gams/loggers/GlobalLogger.h"
#include "producer.h"

namespace knowledge = madara::knowledge;

// constructor
threads::producer::producer ()
{
}

// destructor
threads::producer::~producer ()
{
}

/**
 * Initialization to a knowledge base. If you don't actually need access
 * to the knowledge base, just scheduling things in madara::threads::Threader,
 * then you can decide to delete this function or simply do nothing inside of
 * the function.
 **/
void
threads::producer::init (knowledge::KnowledgeBase & knowledge)
{
  // point our data plane to the knowledge base initializing the thread
  data_ = knowledge;

  // name our Integer in the KnowledgeBase
  random_number.set_name("random_number", knowledge);
}

/**
 * Executes the actual thread logic. Best practice is to simply do one loop
 * iteration. If you want a long running thread that executes something
 * frequently, see the madara::threads::Threader::runHz method in your
 * controller.
 **/
void
threads::producer::run (void)
{
  /**
   * the MADARA logger is thread-safe, fast, and allows for specifying
   * various options like output files and multiple output targets (
   * e.g., std::cerr, a system log, and a thread_output.txt file). You
   * can create your own custom log levels or loggers as well.
   **/
  madara_logger_ptr_log (gams::loggers::global_logger.get (),
    gams::loggers::LOG_ALWAYS,
    "threads::producer::run:" 
    " executing\n");

  // modify the random_number stored in the KnowledgeBase
  int64_t rn = rand() % 100;
  random_number = rn;

  // print out the record we added to KnowledgeBase
  std::ostringstream message;
  message << "Producer made " << rn << std::endl;
  data_.print(message.str(), 0);

}
