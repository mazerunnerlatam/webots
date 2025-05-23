/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (https://www.swig.org).
 * Version 4.2.1
 *
 * Do not make changes to this file unless you know what you are doing - modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.cyberbotics.webots.controller;

public class Compass extends Device {
  private transient long swigCPtr;

  protected Compass(long cPtr, boolean cMemoryOwn) {
    super(wrapperJNI.Compass_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Compass obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected static long swigRelease(Compass obj) {
    long ptr = 0;
    if (obj != null) {
      if (!obj.swigCMemOwn)
        throw new RuntimeException("Cannot release ownership as memory is not owned");
      ptr = obj.swigCPtr;
      obj.swigCMemOwn = false;
      obj.delete();
    }
    return ptr;
  }

  @SuppressWarnings({"deprecation", "removal"})
  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        wrapperJNI.delete_Compass(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public Compass(String name) {
    this(wrapperJNI.new_Compass__SWIG_0(name), true);
  }

  public Compass(int tag) {
    this(wrapperJNI.new_Compass__SWIG_1(tag), true);
  }

  public void enable(int samplingPeriod) {
    wrapperJNI.Compass_enable(swigCPtr, this, samplingPeriod);
  }

  public void disable() {
    wrapperJNI.Compass_disable(swigCPtr, this);
  }

  public int getSamplingPeriod() {
    return wrapperJNI.Compass_getSamplingPeriod(swigCPtr, this);
  }

  public double[] getValues() {
    return wrapperJNI.Compass_getValues(swigCPtr, this);
  }

  private int getLookupTableSize() {
    return wrapperJNI.Compass_getLookupTableSize(swigCPtr, this);
  }

  public double[] getLookupTable() {
    return wrapperJNI.Compass_getLookupTable(swigCPtr, this);
  }

}
