/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkMorphologicalWatershedImageFilter.h,v $
  Language:  C++
  Date:      $Date: 2005/08/23 15:09:03 $
  Version:   $Revision: 1.4 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkFFTShiftImageFilter_h
#define __itkFFTShiftImageFilter_h

#include "itkImageToImageFilter.h"

namespace itk {

/** \class FFTShiftImageFilter
 * \brief Shift the zero-frequency components to center of the image
 *
 * The fourier transform produce an image where the zero frequency components are in the corner
 * of the image, making it difficult to understand. This filter shift the component to the center
 * of the image.
 * Note that with images with odd size, applying this filter twice will not produce the same image
 * than the original one without using SetInverse(true) on one (and only one) of the two filters.
 *
 * \author Gaetan Lehmann. Biologie du Développement et de la Reproduction, INRA de Jouy-en-Josas, France.
 *
 * \sa FFTRealToComplexConjugateImageFilter, FFTComplexConjugateToRealImageFilter, FFTWRealToComplexConjugateImageFilter, FFTWComplexConjugateToRealImageFilter, Log10ImageFilter, RescaleIntensityImageFilter
 */
template<class TInputImage, class TOutputImage>
class ITK_EXPORT FFTShiftImageFilter : 
    public ImageToImageFilter<TInputImage, TOutputImage>
{
public:
  /** Standard class typedefs. */
  typedef FFTShiftImageFilter Self;
  typedef ImageToImageFilter<TInputImage, TOutputImage>
  Superclass;
  typedef SmartPointer<Self>        Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  /** Some convenient typedefs. */
  typedef TInputImage InputImageType;
  typedef TOutputImage OutputImageType;
  typedef typename InputImageType::Pointer         InputImagePointer;
  typedef typename InputImageType::ConstPointer    InputImageConstPointer;
  typedef typename InputImageType::RegionType      InputImageRegionType;
  typedef typename InputImageType::PixelType       InputImagePixelType;
  typedef typename OutputImageType::Pointer        OutputImagePointer;
  typedef typename OutputImageType::ConstPointer   OutputImageConstPointer;
  typedef typename OutputImageType::RegionType     OutputImageRegionType;
  typedef typename OutputImageType::PixelType      OutputImagePixelType;
  typedef typename OutputImageType::IndexType      IndexType;
  typedef typename OutputImageType::SizeType       SizeType;
  
  /** ImageDimension constants */
  itkStaticConstMacro(ImageDimension, unsigned int,
                      TInputImage::ImageDimension);

  /** Standard New method. */
  itkNewMacro(Self);  

  /** Runtime information support. */
  itkTypeMacro(FFTShiftImageFilter, 
               ImageToImageFilter);

  /**
   * Set/Get whether the filter must perform an inverse transform or not.
   * This option has no effect if none of the size of the input image is odd,
   * but is required to be able to restore the original image if at least one
   * of the size is odd.
   */
  itkSetMacro(Inverse, bool);
  itkGetConstReferenceMacro(Inverse, bool);
  itkBooleanMacro(Inverse);

protected:
  FFTShiftImageFilter();
  ~FFTShiftImageFilter() {};
  void PrintSelf(std::ostream& os, Indent indent) const;

  /** FFTShiftImageFilter needs the entire input be
   * available. Thus, it needs to provide an implementation of
   * GenerateInputRequestedRegion(). */
  void GenerateInputRequestedRegion() ;


  /** Multi-thread version GenerateData. */
  void  ThreadedGenerateData (const OutputImageRegionType& 
                              outputRegionForThread,
                              int threadId) ;
  

private:
  FFTShiftImageFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  bool m_Inverse;

} ; // end of class

} // end namespace itk
  
#ifndef ITK_MANUAL_INSTANTIATION
#include "itkFFTShiftImageFilter.txx"
#endif

#endif


