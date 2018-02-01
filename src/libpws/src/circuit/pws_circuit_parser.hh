#pragma once

#include <map>
#include <gmp.h>
#include <iterator>
#include <numeric>
#include <set>
#include <stdint.h>
#include <string>
#include <vector>

#include "maybe.hh"
#include "pws_primitives.hh"
#include "tokenizer.hh"

// for de-duplicating gates
typedef uint64_t GateMapID;

// Required predeclaration.
class MagicVarOperation;

class PWSCircuitParser
{
  std::map<int, CVar*> varMap;
  std::map<int, CVar*> inOutVarsMap;



  // These are the constant outputs.
  std::vector<ConstOutputDescription> outConstantDesc;

  //TODO: Unpublic this.
  std::vector<CConst*> constants;
  std::map<std::string, int> constMap;

  std::string token;

  public:
  CircuitDescription circuitDesc;

  //vector of maps from mux gate indexes at each layer to index of mux control bit.
  std::vector<std::map<int, int> > muxGates;
  //keep track of how big the bool vec should be.
  int largestMuxBitIndex;

  // These are instructions on how to deal with "magic" variables, and a guard
  // that says at which point in the operation order is the operation allowed to
  // be executed.
  std::vector< std::pair<std::vector<int>, MagicVarOperation*> > magicOps;

  // Inverted indeces.
  std::map<std::string, std::vector<int> > outConstants;
  std::vector< std::pair<std::string, int> > inConstants;

  int outputGateBegin;
  std::map<int, int> inGates;
  std::map<int, int> outGates;
  std::vector<int> magicGates;



  PWSOpCount opCount;
  mpz_t prime;

  public:
  PWSCircuitParser(const mpz_t prime);

  void clear();

  const CircuitDescription& getCircuitDescription() const;

  void parse(const std::string& pwsFileName);
  void optimize(const std::string &pwsFileName);

  void printCircuitDescription();
  void printCircuitStats();
  void printMemoryStats() const;

  LayerDescription& getLayer(int layerNum);
  GateDescription& getGate(const GatePosition pos);

  private:
  GatePosition getGate(const Primitive& p, int layer = 0);
  GatePosition getGate(CPrimitive& p, int layer = 0);

  CPrimitive& getCircuitPrimitive(const Primitive& p);
  Maybe<CVar*> getCircuitVariable(const Primitive& p);
  Maybe<CConst*> getCircuitConstant(const Primitive& p);

  void remove_gates_from_layer(std::set<unsigned> &removes, LayerDescription &thisL, LayerDescription &prevL);
  GateMapID compute_gate_id(GateDescription &gate);

  void getOpGuard(std::vector<int>& guard);
  std::map<int, CVar*>& getVarMap(const Primitive& p);

  void clearPrivate();
  void clearIndexes();

  GatePosition addGate(GateDescription::OpType op, int in1, int in2, int outLayerNum);
  void addToCircuit(CPrimitive& p);

  CVar& addVariable(CVar::VarType type, int name);
  CConst& addConstant(const std::string& constant);
  CConst& addConstant(int constant);
  CConst& addConstant(mpz_t constant);

  void addMagicOp(MagicVarOperation* op, std::vector<int>& guard);

  GatePosition promotePrimitive(CPrimitive& p, int layer);
  GatePosition promoteGate(const GatePosition g, int layer);

  void bindPrimitive(const Primitive& var, const GatePosition gate);
  void bindVariable(const Primitive& var, const GatePosition gate);
  void bindOutputConstant(const GatePosition outGate, int val);
  void bindOutputConstant(const Primitive val, const GatePosition outGate);

  Primitive makeMagic(const Primitive var);

  GatePosition makeGate(const GateDescription::OpType op, const GatePosition in1, const GatePosition in2);
  GatePosition makeGate(const GateDescription::OpType op, const Primitive& in1, const Primitive& in2);
  GatePosition makeGate(const GateDescription::OpType op, CPrimitive& in1, CPrimitive& in2, int inLayerNum);

  GatePosition makeSubGate(const GatePosition in1, const GatePosition in2);
  GatePosition makeZeroOrOtherGate(CPrimitive& var, mpz_t other);

  GatePosition negatePrimitive(const Primitive& p);
  GatePosition negateGate(const GatePosition g);
  GatePosition reduce(const GateDescription::OpType op, const std::vector<GatePosition>& terms);

  Maybe<Primitive> parsePrimitive(Tokenizer& pws);
  Maybe<Primitive> parseVar(const std::string& token);
  Maybe<Primitive> parseConst(const std::string& token);

  Maybe<GatePosition> parsePoly(Tokenizer& pws, const std::string end = ")");
  Maybe<GatePosition> parsePolyTerm(Tokenizer& pws, GateDescription::OpType &polyOp);

  void parsePolyConstraint(Tokenizer& pws);
  void parseLessThanInt(Tokenizer& pws);
  void parseLessThanFloat(Tokenizer& pws);
  void parseNotEqual(Tokenizer& pws);
  void parseDivide(Tokenizer& pws);
  void parseMux(Tokenizer& pws);
  void makeOutputLayer();
  void constructInvertedIndexes();
};
