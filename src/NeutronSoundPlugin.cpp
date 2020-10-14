#include <NeutronSoundPlugin.hpp>
#include <plugin/callbacks.hpp>

::rack::plugin::Plugin* pluginInstance;

void init(::rack::plugin::Plugin* p)
{
   pluginInstance = p;

   p->addModel(modelOrgoneAccumulator);
}
