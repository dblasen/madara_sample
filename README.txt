Remade the repo. Here's what we have:

1) A `producer` thread that generates a random integer and stores
    it in the KnowledgeBase. It also increments a counter on each
    iteration that's used to trigger a filter after 10 cycles.
    It announces every number it makes.

2) A `consumer` thread that pulls the random integer from the
    KnowledgeBase and squares it. It announces both numbers.
    Periodically (5 iterations) it will write the KnowledgeBase
    to JSON file.

The sample uses ZMQ for transport and implements a simple filter
intended to engage after 10 iterations of the `producer` thread
but I'm not sure that's working quite as intended.
