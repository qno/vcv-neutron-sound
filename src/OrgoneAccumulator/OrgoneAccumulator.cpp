#include <NeutronSoundPlugin.hpp>
#include <rack.hpp>

using namespace rack;

struct OrgoneAccumulator : Module
{
   enum ParamIds
   {
      KNOB_A_WAVE_PARAM,
      KNOB_B_WAVE_PARAM,
      KNOB_C_WAVE_PARAM,
      KNOB_MOD_WAVE_PARAM,
      SWITCH_PULS_PARAM,
      SWITCH_A_PARAM,
      SWITCH_B_PARAM,
      SWITCH_CX_PARAM,
      SWITCH_FX_PARAM,
      SWITCH_C_PARAM,
      SWITCH_FM_PARAM,
      SWITCH_FIX_PARAM,
      KNOB_EFFECT_PARAM,
      KNOB_INDEX_PARAM,
      KNOB_TUNE_PARAM,
      KNOB_SCAN_PARAM,
      KNOB_FREQUENCY_PARAM,
      SWITCH_TUNELOCK_PARAM,
      KNOB_FINETUNE_PARAM,
      KNOB_SCAN_ATT_PARAM,
      KNOB_INDEX_ATT_PARAM,
      KNOB_FREQUENCY_ATT_PARAM,
      KNOB_EFFECT_ATT_PARAM,
      NUM_PARAMS
   };
   enum InputIds
   {
      RESET_INPUT,
      CV_SCAN_INPUT,
      V_OCTAVE_INPUT,
      CV_EFFECT_INPUT,
      CV_INDEX_INPUT,
      CV_FREQUENCY_INPUT,
      CV_A_INPUT,
      CV_B_INPUT,
      CV_MOD_INPUT,
      CV_C_INPUT,
      NUM_INPUTS
   };
   enum OutputIds
   {
      MAIN_OUTPUT,
      PWM_SUB_OUTPUT,
      NUM_OUTPUTS
   };
   enum LightIds
   {
      ENUMS(A_LIGHT, 3),
      ENUMS(FM_LIGHT, 3),
      ENUMS(PULS_LIGHT, 3),
      ENUMS(B_LIGHT, 3),
      ENUMS(C_LIGHT, 3),
      ENUMS(CX_LIGHT, 3),
      ENUMS(FX_LIGHT, 3),
      ENUMS(FIX_LIGHT, 3),
      ENUMS(TUNELOCK_LIGHT, 3),
      ENUMS(FINE_LIGHT, 3),
      NUM_LIGHTS
   };
   
   OrgoneAccumulator()
   {
      config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
      configParam(KNOB_A_WAVE_PARAM, 0.f, 1.f, 0.f, "");
      configParam(KNOB_B_WAVE_PARAM, 0.f, 1.f, 0.f, "");
      configParam(KNOB_C_WAVE_PARAM, 0.f, 1.f, 0.f, "");
      configParam(KNOB_MOD_WAVE_PARAM, 0.f, 1.f, 0.f, "");
      configParam(SWITCH_PULS_PARAM, 0.f, 1.f, 0.f, "");
      configParam(SWITCH_A_PARAM, 0.f, 1.f, 0.f, "");
      configParam(SWITCH_B_PARAM, 0.f, 1.f, 0.f, "");
      configParam(SWITCH_CX_PARAM, 0.f, 1.f, 0.f, "");
      configParam(SWITCH_FX_PARAM, 0.f, 1.f, 0.f, "");
      configParam(SWITCH_C_PARAM, 0.f, 1.f, 0.f, "");
      configParam(SWITCH_FM_PARAM, 0.f, 1.f, 0.f, "");
      configParam(SWITCH_FIX_PARAM, 0.f, 1.f, 0.f, "");
      configParam(KNOB_EFFECT_PARAM, 0.f, 1.f, 0.f, "");
      configParam(KNOB_INDEX_PARAM, 0.f, 1.f, 0.f, "");
      configParam(KNOB_TUNE_PARAM, 0.f, 1.f, 0.f, "");
      configParam(KNOB_SCAN_PARAM, 0.f, 1.f, 0.f, "");
      configParam(KNOB_FREQUENCY_PARAM, 0.f, 1.f, 0.f, "");
      configParam(SWITCH_TUNELOCK_PARAM, 0.f, 1.f, 0.f, "");
      configParam(KNOB_FINETUNE_PARAM, 0.f, 1.f, 0.f, "");
      configParam(KNOB_SCAN_ATT_PARAM, 0.f, 1.f, 0.f, "");
      configParam(KNOB_INDEX_ATT_PARAM, 0.f, 1.f, 0.f, "");
      configParam(KNOB_FREQUENCY_ATT_PARAM, 0.f, 1.f, 0.f, "");
      configParam(KNOB_EFFECT_ATT_PARAM, 0.f, 1.f, 0.f, "");
   }
   
   void process(const ProcessArgs& args) override
   {
      auto volt_a = inputs[CV_A_INPUT].getVoltage();
      auto volt_b = inputs[CV_B_INPUT].getVoltage();
      auto volt_c = inputs[CV_C_INPUT].getVoltage();
      lights[A_LIGHT + 0].setBrightness(volt_a);
      lights[A_LIGHT + 1].setBrightness(volt_b);
      lights[A_LIGHT + 2].setBrightness(volt_c);
   }
};

struct OrgoneAccumulatorWidget : ModuleWidget {
   OrgoneAccumulatorWidget(OrgoneAccumulator* module) {
      setModule(module);
      setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/OrgoneAccumulator/Module.svg")));

      addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
      addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
      addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
      addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

      addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(12.02, 18.101)), module, OrgoneAccumulator::KNOB_A_WAVE_PARAM));
      addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(35.547, 18.148)), module, OrgoneAccumulator::KNOB_B_WAVE_PARAM));
      addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(59.12, 18.241)), module, OrgoneAccumulator::KNOB_C_WAVE_PARAM));
      addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(90.551, 18.241)), module, OrgoneAccumulator::KNOB_MOD_WAVE_PARAM));
      addParam(createParamCentered<CKSS>(mm2px(Vec(20.767, 33.863)), module, OrgoneAccumulator::SWITCH_PULS_PARAM));
      addParam(createParamCentered<CKSS>(mm2px(Vec(9.167, 33.91)), module, OrgoneAccumulator::SWITCH_A_PARAM));
      addParam(createParamCentered<CKSS>(mm2px(Vec(32.179, 33.957)), module, OrgoneAccumulator::SWITCH_B_PARAM));
      addParam(createParamCentered<CKSS>(mm2px(Vec(66.604, 33.957)), module, OrgoneAccumulator::SWITCH_CX_PARAM));
      addParam(createParamCentered<CKSS>(mm2px(Vec(43.592, 34.05)), module, OrgoneAccumulator::SWITCH_FX_PARAM));
      addParam(createParamCentered<CKSS>(mm2px(Vec(55.098, 34.05)), module, OrgoneAccumulator::SWITCH_C_PARAM));
      addParam(createParamCentered<CKSS>(mm2px(Vec(77.735, 34.144)), module, OrgoneAccumulator::SWITCH_FM_PARAM));
      addParam(createParamCentered<CKSS>(mm2px(Vec(89.335, 34.144)), module, OrgoneAccumulator::SWITCH_FIX_PARAM));
      addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(53.975, 50.982)), module, OrgoneAccumulator::KNOB_EFFECT_PARAM));
      addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(72.497, 51.169)), module, OrgoneAccumulator::KNOB_INDEX_PARAM));
      addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(12.441, 51.262)), module, OrgoneAccumulator::KNOB_TUNE_PARAM));
      addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(36.015, 51.262)), module, OrgoneAccumulator::KNOB_SCAN_PARAM));
      addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(90.551, 51.262)), module, OrgoneAccumulator::KNOB_FREQUENCY_PARAM));
      addParam(createParamCentered<CKSS>(mm2px(Vec(18.522, 63.891)), module, OrgoneAccumulator::SWITCH_TUNELOCK_PARAM));
      addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(12.348, 78.203)), module, OrgoneAccumulator::KNOB_FINETUNE_PARAM));
      addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(36.202, 78.297)), module, OrgoneAccumulator::KNOB_SCAN_ATT_PARAM));
      addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(71.936, 78.484)), module, OrgoneAccumulator::KNOB_INDEX_ATT_PARAM));
      addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(90.27, 78.484)), module, OrgoneAccumulator::KNOB_FREQUENCY_ATT_PARAM));
      addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(54.069, 78.577)), module, OrgoneAccumulator::KNOB_EFFECT_ATT_PARAM));

      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(21.702, 98.034)), module, OrgoneAccumulator::RESET_INPUT));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.734, 98.034)), module, OrgoneAccumulator::CV_SCAN_INPUT));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.624, 98.128)), module, OrgoneAccumulator::V_OCTAVE_INPUT));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(53.694, 98.128)), module, OrgoneAccumulator::CV_EFFECT_INPUT));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(71.468, 98.128)), module, OrgoneAccumulator::CV_INDEX_INPUT));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(89.148, 98.128)), module, OrgoneAccumulator::CV_FREQUENCY_INPUT));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.921, 112.16)), module, OrgoneAccumulator::CV_A_INPUT));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(53.788, 112.16)), module, OrgoneAccumulator::CV_B_INPUT));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(89.335, 112.16)), module, OrgoneAccumulator::CV_MOD_INPUT));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(71.561, 112.253)), module, OrgoneAccumulator::CV_C_INPUT));

      addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.974, 112.352)), module, OrgoneAccumulator::MAIN_OUTPUT));
      addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(21.843, 112.394)), module, OrgoneAccumulator::PWM_SUB_OUTPUT));

      addChild(createLightCentered<SmallLight<RedGreenBlueLight>>(mm2px(Vec(13.049, 29.654)), module, OrgoneAccumulator::A_LIGHT));
      addChild(createLightCentered<SmallLight<RedGreenBlueLight>>(mm2px(Vec(81.851, 29.654)), module, OrgoneAccumulator::FM_LIGHT));
      addChild(createLightCentered<SmallLight<RedGreenBlueLight>>(mm2px(Vec(24.696, 29.841)), module, OrgoneAccumulator::PULS_LIGHT));
      addChild(createLightCentered<SmallLight<RedGreenBlueLight>>(mm2px(Vec(36.108, 29.841)), module, OrgoneAccumulator::B_LIGHT));
      addChild(createLightCentered<SmallLight<RedGreenBlueLight>>(mm2px(Vec(58.933, 29.841)), module, OrgoneAccumulator::C_LIGHT));
      addChild(createLightCentered<SmallLight<RedGreenBlueLight>>(mm2px(Vec(70.439, 29.841)), module, OrgoneAccumulator::CX_LIGHT));
      addChild(createLightCentered<SmallLight<RedGreenBlueLight>>(mm2px(Vec(47.521, 29.934)), module, OrgoneAccumulator::FX_LIGHT));
      addChild(createLightCentered<SmallLight<RedGreenBlueLight>>(mm2px(Vec(92.983, 30.028)), module, OrgoneAccumulator::FIX_LIGHT));
      addChild(createLightCentered<SmallLight<RedLight>>(mm2px(Vec(13.096, 63.797)), module, OrgoneAccumulator::TUNELOCK_LIGHT));
      addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(7.951, 90.083)), module, OrgoneAccumulator::FINE_LIGHT));
   }
};


Model* modelOrgoneAccumulator = createModel<OrgoneAccumulator, OrgoneAccumulatorWidget>("OrgoneAccumulator");
