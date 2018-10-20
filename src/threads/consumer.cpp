#include <iostream>

#include "gams/loggers/GlobalLogger.h"
#include "consumer.h"

namespace knowledge = madara::knowledge;

// constructor
threads::consumer::consumer ()
{
}

// destructor
threads::consumer::~consumer ()
{
}

/**
 * Initialization to a knowledge base. If you don't actually need access
 * to the knowledge base, just scheduling things in madara::threads::Threader,
 * then you can decide to delete this function or simply do nothing inside of
 * the function.
 **/
void
threads::consumer::init (knowledge::KnowledgeBase & knowledge)
{
  // point our data plane to the knowledge base initializing the thread
  data_ = knowledge;
}

/**
 * Executes the actual thread logic. Best practice is to simply do one loop
 * iteration. If you want a long running thread that executes something
 * frequently, see the madara::threads::Threader::runHz method in your
 * controller.
 **/
void
threads::consumer::run (void)
{
  /**
   * the MADARA logger is thread-safe, fast, and allows for specifying
   * various options like output files and multiple output targets (
   * e.g., std::cerr, a system log, and a thread_output.txt file). You
   * can create your own custom log levels or loggers as well.
   **/
  madara_logger_ptr_log (gams::loggers::global_logger.get (),
    gams::loggers::LOG_MAJOR,
    "threads::consumer::run:" 
    " executing\n");

  //variables
  std::ostringstream message;
  int64_t random_number_in = 0;
  int64_t random_number_modified = 0;
  //pull the Integer from KnowledgeBase
  random_number_in = data_.get("random_number").to_integer();
  //make sure we actually have a number to work with...
  if(random_number_in)
  {
    //square the number from KnowledgeBase, build a message to print, and print it out.
    random_number_modified = random_number_in * random_number_in;
    message << "Consumer found " << random_number_in << " and changed it to " << random_number_modified << std::endl;
    data_.print(message.str(), 0);
  }
}
