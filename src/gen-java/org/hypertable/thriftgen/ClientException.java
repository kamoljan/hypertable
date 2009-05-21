/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 */
package org.hypertable.thriftgen;

import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.Set;
import java.util.HashSet;
import java.util.Collections;

import org.apache.thrift.*;
import org.apache.thrift.meta_data.*;
import org.apache.thrift.protocol.*;

/**
 * Exception for thrift clients.
 * 
 * <dl>
 *   <dt>code</dt><dd>Internal use (defined in src/cc/Common/Error.h)</dd>
 *   <dt>what</dt><dd>A message about the exception</dd>
 * </dl>
 * 
 * Note: some languages (like php) don't have adequate namespace, so Exception
 * would conflict with language builtins.
 */
public class ClientException extends Exception implements TBase, java.io.Serializable, Cloneable {
  private static final TStruct STRUCT_DESC = new TStruct("ClientException");
  private static final TField CODE_FIELD_DESC = new TField("code", TType.I32, (short)1);
  private static final TField WHAT_FIELD_DESC = new TField("what", TType.STRING, (short)2);

  public int code;
  public static final int CODE = 1;
  public String what;
  public static final int WHAT = 2;

  private final Isset __isset = new Isset();
  private static final class Isset implements java.io.Serializable {
    public boolean code = false;
  }

  public static final Map<Integer, FieldMetaData> metaDataMap = Collections.unmodifiableMap(new HashMap<Integer, FieldMetaData>() {{
    put(CODE, new FieldMetaData("code", TFieldRequirementType.DEFAULT, 
        new FieldValueMetaData(TType.I32)));
    put(WHAT, new FieldMetaData("what", TFieldRequirementType.DEFAULT, 
        new FieldValueMetaData(TType.STRING)));
  }});

  static {
    FieldMetaData.addStructMetaDataMap(ClientException.class, metaDataMap);
  }

  public ClientException() {
  }

  public ClientException(
    int code,
    String what)
  {
    this();
    this.code = code;
    this.__isset.code = true;
    this.what = what;
  }

  /**
   * Performs a deep copy on <i>other</i>.
   */
  public ClientException(ClientException other) {
    __isset.code = other.__isset.code;
    this.code = other.code;
    if (other.isSetWhat()) {
      this.what = other.what;
    }
  }

  @Override
  public ClientException clone() {
    return new ClientException(this);
  }

  public int getCode() {
    return this.code;
  }

  public void setCode(int code) {
    this.code = code;
    this.__isset.code = true;
  }

  public void unsetCode() {
    this.__isset.code = false;
  }

  // Returns true if field code is set (has been asigned a value) and false otherwise
  public boolean isSetCode() {
    return this.__isset.code;
  }

  public void setCodeIsSet(boolean value) {
    this.__isset.code = value;
  }

  public String getWhat() {
    return this.what;
  }

  public void setWhat(String what) {
    this.what = what;
  }

  public void unsetWhat() {
    this.what = null;
  }

  // Returns true if field what is set (has been asigned a value) and false otherwise
  public boolean isSetWhat() {
    return this.what != null;
  }

  public void setWhatIsSet(boolean value) {
    if (!value) {
      this.what = null;
    }
  }

  public void setFieldValue(int fieldID, Object value) {
    switch (fieldID) {
    case CODE:
      if (value == null) {
        unsetCode();
      } else {
        setCode((Integer)value);
      }
      break;

    case WHAT:
      if (value == null) {
        unsetWhat();
      } else {
        setWhat((String)value);
      }
      break;

    default:
      throw new IllegalArgumentException("Field " + fieldID + " doesn't exist!");
    }
  }

  public Object getFieldValue(int fieldID) {
    switch (fieldID) {
    case CODE:
      return new Integer(getCode());

    case WHAT:
      return getWhat();

    default:
      throw new IllegalArgumentException("Field " + fieldID + " doesn't exist!");
    }
  }

  // Returns true if field corresponding to fieldID is set (has been asigned a value) and false otherwise
  public boolean isSet(int fieldID) {
    switch (fieldID) {
    case CODE:
      return isSetCode();
    case WHAT:
      return isSetWhat();
    default:
      throw new IllegalArgumentException("Field " + fieldID + " doesn't exist!");
    }
  }

  @Override
  public boolean equals(Object that) {
    if (that == null)
      return false;
    if (that instanceof ClientException)
      return this.equals((ClientException)that);
    return false;
  }

  public boolean equals(ClientException that) {
    if (that == null)
      return false;

    boolean this_present_code = true;
    boolean that_present_code = true;
    if (this_present_code || that_present_code) {
      if (!(this_present_code && that_present_code))
        return false;
      if (this.code != that.code)
        return false;
    }

    boolean this_present_what = true && this.isSetWhat();
    boolean that_present_what = true && that.isSetWhat();
    if (this_present_what || that_present_what) {
      if (!(this_present_what && that_present_what))
        return false;
      if (!this.what.equals(that.what))
        return false;
    }

    return true;
  }

  @Override
  public int hashCode() {
    return 0;
  }

  public void read(TProtocol iprot) throws TException {
    TField field;
    iprot.readStructBegin();
    while (true)
    {
      field = iprot.readFieldBegin();
      if (field.type == TType.STOP) { 
        break;
      }
      switch (field.id)
      {
        case CODE:
          if (field.type == TType.I32) {
            this.code = iprot.readI32();
            this.__isset.code = true;
          } else { 
            TProtocolUtil.skip(iprot, field.type);
          }
          break;
        case WHAT:
          if (field.type == TType.STRING) {
            this.what = iprot.readString();
          } else { 
            TProtocolUtil.skip(iprot, field.type);
          }
          break;
        default:
          TProtocolUtil.skip(iprot, field.type);
          break;
      }
      iprot.readFieldEnd();
    }
    iprot.readStructEnd();


    // check for required fields of primitive type, which can't be checked in the validate method
    validate();
  }

  public void write(TProtocol oprot) throws TException {
    validate();

    oprot.writeStructBegin(STRUCT_DESC);
    oprot.writeFieldBegin(CODE_FIELD_DESC);
    oprot.writeI32(this.code);
    oprot.writeFieldEnd();
    if (this.what != null) {
      oprot.writeFieldBegin(WHAT_FIELD_DESC);
      oprot.writeString(this.what);
      oprot.writeFieldEnd();
    }
    oprot.writeFieldStop();
    oprot.writeStructEnd();
  }

  @Override
  public String toString() {
    StringBuilder sb = new StringBuilder("ClientException(");
    boolean first = true;

    sb.append("code:");
    sb.append(this.code);
    first = false;
    if (!first) sb.append(", ");
    sb.append("what:");
    if (this.what == null) {
      sb.append("null");
    } else {
      sb.append(this.what);
    }
    first = false;
    sb.append(")");
    return sb.toString();
  }

  public void validate() throws TException {
    // check for required fields
    // check that fields of type enum have valid values
  }

}

