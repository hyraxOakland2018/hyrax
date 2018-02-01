#pragma once

#include <sstream>
#include <vector>

#include "circuit_layer.hh"
#include "maybe.hh"

struct Primitive
{
  enum PrimitiveType {
    CONSTANT,
    INTERMEDIATE,
    INPUT_OUTPUT
  };

  PrimitiveType pType;
  int idx;

  Primitive()
  {
    pType = CONSTANT;
    idx = 0;
  }

  Primitive(PrimitiveType t, int i)
  {
    pType = t;
    idx = i;
  }

  void makeIntermediate(int name)
  {
    pType = INTERMEDIATE;
    idx = name;
  }

  void makeInputOutput(int name)
  {
    pType = INPUT_OUTPUT;
    idx = name;
  }

  void makeConstant(int i)
  {
    pType = CONSTANT;
    idx = i;
  }

  bool isConstant() const { return pType == CONSTANT; }
  bool isVariable() const { return isInputOutput() || pType == INTERMEDIATE; }
  bool isInputOutput() const { return pType == INPUT_OUTPUT; }
};

struct GatePosition
{
  int layer;
  int name;

  GatePosition()
    : layer(0), name(0)
  { }

  GatePosition(int l, int n)
    : layer(l), name(n)
  { }

  friend std::ostream& operator<<(std::ostream& os, const GatePosition& pos)
  {
    return os << "(" << pos.layer << ", " << pos.name << ")";
  }
};

struct GateDescription
{
  enum OpType {
    ADD,
    MUL,
    DIV_INT,    // This is a special case.
    CONSTANT,
    SUB,
    MUX,
    OR,
    XOR,
    NOT,
    NAND,
    NOR,
    NXOR,
    NAAB,
    PASS,
  };

  OpType op;
  GatePosition pos;
  int in1;
  int in2;

  Maybe<Primitive> boundPrimitive;

  public:
  GateDescription() {}
  GateDescription(int n)
    : op(CONSTANT), pos(0, n), in1(0), in2(0)
  { }
  GateDescription(OpType o, int l, int n, int i1, int i2)
    : op(o), pos(l, n), in1(i1), in2(i2)
  { }

  void makeGate(GateWiring& wiring) const
  {
    GateWiring::GateType gateOp;
    switch (op)
    {
      case ADD:
        gateOp = GateWiring::ADD;
        break;
      case MUL:
        gateOp = GateWiring::MUL;
        break;
      case DIV_INT:
        gateOp = GateWiring::DIV_INT;
        break;
    case SUB:
        gateOp = GateWiring::SUB;
        break;
    case MUX:
        gateOp = GateWiring::MUX;
        break;
    case OR:
        gateOp = GateWiring::OR;
        break;
    case XOR:
        gateOp = GateWiring::XOR;
        break;
    case NOT:
        gateOp = GateWiring::NOT;
        break;
    case NAND:
        gateOp = GateWiring::NAND;
        break;
    case NOR:
        gateOp = GateWiring::NOR;
        break;
    case NXOR:
        gateOp = GateWiring::NXOR;
        break;
    case NAAB:
        gateOp = GateWiring::NAAB;
        break;
    case PASS:
        gateOp = GateWiring::PASS;
        break;
    default:
        gateOp = GateWiring::ADD;
    }

    wiring.setWiring(gateOp, in1, in2);
  }

  bool isBound() const         { return boundPrimitive.isValid(); }
  void bind(const Primitive p) { boundPrimitive = p; }
  void unbind()                { boundPrimitive.invalidate(); }

  bool isConstant() const { return op == CONSTANT; }
  std::string strOpType()
  {
    switch (op)
    {
      case ADD:
        return "ADD";
      case MUL:
        return "MUL";
      case DIV_INT:
        return "DIVI";
      case CONSTANT:
        return "CON";
    case SUB:
        return "SUB";
    case MUX:
        return "MUX";
    case OR:
        return "OR";
    case XOR:
        return "XOR";
    case NOT:
        return "NOT";
    case NAND:
        return "NAND";
    case NOR:
        return "NOR";
    case NXOR:
        return "NXOR";
    case NAAB:
        return "NAAB";
    case PASS:
        return "PASS";
    default:
        return "";
    }
  }
};

struct CPrimitive
{
  int minLayer;
  int maxLayer;

  std::vector<int> gateIndex;

  CPrimitive()
  {
    minLayer = maxLayer = -1;
  }

  virtual ~CPrimitive() { }

  int minMatchingLayer(const CPrimitive& other) const
  {
    return std::max(minLayer, other.minLayer);
  }

  bool isBound() const { return !gateIndex.empty(); }
  void bind(const GatePosition gate)
  {
    //TODO
    minLayer = maxLayer = gate.layer;
    gateIndex.clear();
    gateIndex.push_back(gate.name);
  }

  virtual Primitive toPrimitive() const = 0;
  virtual std::string toString() const = 0;

  friend std::ostream& operator<<(std::ostream& os, const CPrimitive& p)
  {
    return os << p.toString();
  }
};

struct CConst : public CPrimitive
{
  std::string value;
  int name;

  CConst(const std::string& c, int n)
    : value(c), name(n)
  { }

  Primitive toPrimitive() const
  {
    return Primitive(Primitive::CONSTANT, name);
  }

  std::string toString() const { return value; }
};

struct CVar : public CPrimitive
{
  enum VarType {
    INPUT,
    OUTPUT,
    MAGIC,
    TEMP
  };

  VarType varType;
  int name;

  CVar()
  {
    varType = TEMP;
    name = 0;
  }

  CVar(VarType t, int n)
  {
    varType = t;
    name = n;
  }

  virtual ~CVar() { }

  void makeMagic() { varType = MAGIC; }
  bool isInInputLayer() const { return isInput() || isMagic(); }
  bool isInput() const { return varType == INPUT; }
  bool isMagic() const { return varType == MAGIC; }
  bool isOutput() const { return varType == OUTPUT; }
  bool isIO() const { return isInput() || isOutput(); }

  std::string varTypeStr() const
  {
    switch (varType)
    {
      case INPUT:
        return "I";
      case OUTPUT:
        return "O";
      case MAGIC:
        return "M";
      case TEMP:
        return "V";
      default:
        return "";
    }
  }

  Primitive toPrimitive() const
  {
    if (isIO())
      return Primitive(Primitive::INPUT_OUTPUT, name);
    else
      return Primitive(Primitive::INTERMEDIATE, name);
  }

  std::string toString() const
  {
    std::stringstream ss;
    ss << varTypeStr() << name;
    return ss.str();
  }
};

struct PWSOpCount
{
  size_t numMults;
  size_t numAdds;
  size_t numIntDivs;
  size_t numIneqs;
  size_t numCmps;
  size_t numSubs;
  size_t numMuxs;
  size_t numOrs;
  size_t numXors;
  size_t numNots;
  size_t numNands;
  size_t numNors;
  size_t numNxors;
  size_t numNaabs;
  size_t numPass;
  PWSOpCount()
    : numMults(0), numAdds(0), numIntDivs(0),
      numIneqs(0), numCmps(0), numSubs(0),
      numMuxs(0), numOrs(0), numXors(0),
      numNots(0), numNands(0), numNors(0),
      numNxors(0), numNaabs(0), numPass(0)
  { }

  void clear()
  {
    numMults = 0;
    numAdds = 0;
    numIntDivs = 0;
    numIneqs = 0;
    numCmps = 0;
    numSubs = 0;
    numMuxs = 0;
    numOrs = 0;
    numXors = 0;
    numNots = 0;
    numNands = 0;
    numNors = 0;
    numNxors = 0;
    numNaabs = 0;
    numPass = 0;
  }

  size_t numOps() const
  {
    return numMults + numAdds + numIntDivs + numIneqs + numCmps + numSubs + numMuxs + numOrs + numXors + numNots + numNands + numNors + numNxors + numNaabs + numPass;
  }
};

typedef std::vector<GateDescription> LayerDescription;
typedef std::vector<LayerDescription> CircuitDescription;

typedef std::pair<GatePosition, std::string> ConstOutputDescription;
