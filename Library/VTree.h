#ifndef VTREE_H
#define VTREE_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <algorithm> //pch
#include <vector> //pch
#include <cassert> //pch
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Declaration of CVTreeNode
//---------------------------------------------------------------------------

template<class TType>
class CVTreeNode {
public:
  using CData = TType;
  using CNodeHandler = size_t;
  static constexpr size_t kRootNodeHandler = 0;

  CVTreeNode();
  CVTreeNode(const CData& Data,
             CNodeHandler NodeHandler,
             size_t DistanceToRoot);
  CVTreeNode(CData&& Data,
             CNodeHandler NodeHandler,
             size_t DistanceToRoot);
  CVTreeNode(const CVTreeNode&) = default;
  CVTreeNode(CVTreeNode&&) = default;
  CVTreeNode& operator=(const CVTreeNode&) = default;
  CVTreeNode& operator=(CVTreeNode&&) = default;

  bool isThereChild() const;

  CData Data_;
  CNodeHandler Parent_;
  CNodeHandler FirstChild_;
  CNodeHandler LastChild_;
  CNodeHandler PreviousSibling_;
  CNodeHandler NextSibling_;
  size_t NumberOfChildren_;
  size_t DistanceToRoot_;
};
//---------------------------------------------------------------------------
// Declaration of CVTree
//---------------------------------------------------------------------------

// The vertices of the tree are stored in a vector.
// The class invariants:
// 1) the root is always the first element of the vector
// 2) all elements are sorted with respect to PreOrder
template<class TType>
class CVTree {
public:
  using CNode = CVTreeNode<TType>;
// I have to define several types and constants explicitely
// otherwise I have a compilation error

//using CData = typename CNode::CData;
  using CData = TType;
//using CNodeHandler = typename CNode::CNodeHandler;
  using CNodeHandler = size_t;
  using CVTreeBase = std::vector<CNode>;

//static constexpr size_t kRootNodeHandler = CNode::kRootNodeHandler;
  static constexpr size_t kRootNodeHandler = 0;

  CVTree() = default;
  CVTree(const CData& Data);
  CVTree(const CVTree& Tree) = default;
  CVTree(CVTree&& Tree) = default;
  CVTree& operator=(const CVTree& Tree) = default;
  CVTree& operator=(CVTree&& Tree) = default;
  ~CVTree() = default;

  void destroyExceptRoot();
  inline bool empty() const;
  inline size_t size() const;
  inline void clear();
protected:
  //---------------------------------------------------------------------------
  // Declaration of CConstIteratorDefines
  //---------------------------------------------------------------------------

  class CConstIteratorDefines {
  public:
    using value_type = const CData;
    using difference_type = int;
    using pointer = value_type*;
    using reference = value_type&;
    using CNodeHandler = CNodeHandler;
    using CNode = const CNode;
    using CHostTreePtr = const CVTree<CData>*;
    using CNodeRef = CNode&;
  protected:
    ~CConstIteratorDefines() = default;
  };
  //---------------------------------------------------------------------------
  // Declaration of CIteratorDefines
  //---------------------------------------------------------------------------

  class CIteratorDefines {
  public:
    using value_type = CData;
    using difference_type = int;
    using pointer = value_type*;
    using reference = value_type&;
    using CNodeHandler = CNodeHandler;
    using CNode = CNode;
    using CHostTreePtr = CVTree<CData>*;
    using CNodeRef = CNode&;
  protected:
    ~CIteratorDefines() = default;
  };
  //---------------------------------------------------------------------------
  // Declaration of CBaseIterator
  //---------------------------------------------------------------------------
  template<class TIteratorDefines>
  friend class CBaseIterator;

  template<class TIteratorDefines>
  class CBaseIterator : public TIteratorDefines {
  public:
    template<class TOtherIteratorDefines>
    friend class CBaseIterator;

    using value_type = typename TIteratorDefines::value_type;
    using difference_type = typename TIteratorDefines::difference_type;
    using pointer = typename TIteratorDefines::pointer;
    using reference = typename TIteratorDefines::reference;
    using CNodeHandler = typename TIteratorDefines::CNodeHandler;
    using CHostTreePtr = typename TIteratorDefines::CHostTreePtr;
    using CNode = typename TIteratorDefines::CNode;

    CBaseIterator();
    CBaseIterator(CHostTreePtr HostTree,
                  CNodeHandler Current);
    CBaseIterator(const CBaseIterator& other);
    CBaseIterator(CBaseIterator&& other);
    CBaseIterator& operator=(const CBaseIterator& other);
    CBaseIterator& operator=(CBaseIterator&& other);

    template<class TOtherIteratorDefines>
    bool operator==(const CBaseIterator<TOtherIteratorDefines>& Iterator) const;
    template<class TOtherIteratorDefines>
    bool operator!=(const CBaseIterator<TOtherIteratorDefines>& Iterator) const;

    bool isDefined() const;
    bool isRoot() const;
    bool isLeaf() const;
    bool isThereParent() const;
    bool isThereChild() const;
    bool isThereNextSibling() const;
    bool isTherePreviousSibling() const;

    size_t getNumberOfChildren() const;
    size_t getSizeOfSubTree() const;
    size_t getNumberOfSiblings() const;
    size_t getLengthOfSubTree() const;
    size_t getNumberOfLeaves() const;
    size_t getDistanceToRoot() const;
    size_t getHostSize() const;

    void setToParent();
    void setToFirstChild();
    void setToLastChild();
    void setToNextSibling();
    void setToPreviousSibling();

    void addLastChild(const value_type& NodeData);
    void addLastChild(value_type&& NodeData);

    void changeHost(CHostTreePtr Host);
  protected:
    inline bool isHostDefined() const;
    inline bool isCurrentInFullRange() const;
    inline bool isCurrentInDefinedRange() const;

    inline CNodeHandler getParentHandler() const;
    inline CNodeHandler getFirstChildHandler() const;
    inline CNodeHandler getLastChildHandler() const;
    inline CNodeHandler getPreviousSiblingHandler() const;
    inline CNodeHandler getNextSiblingHandler() const;
    inline CNodeHandler getSubTreeEndHandler() const;


    inline CNode& getNode(const CNodeHandler& Handler);
    inline const CNode& getNode(const CNodeHandler& Handler) const;
    inline CNode& getCurrentNode();
    inline const CNode& getCurrentNode() const;
    inline CNode& getParentNode();
    inline const CNode& getParentNode() const;
    inline CNode& getFirstChildNode();
    inline const CNode& getFirstChildNode() const;
    inline CNode& getLastChildNode();
    inline const CNode& getLastChildNode() const;
    inline CNode& getPreviousSiblingNode();
    inline const CNode& getPreviousSiblingNode() const;
    inline CNode& getNextSiblingNode();
    inline const CNode& getNextSiblingNode() const;

    ~CBaseIterator() = default;
    CHostTreePtr Host_;
    CNodeHandler Current_;
  };
  //---------------------------------------------------------------------------
  // Forward Declaration of CNodeReference
  //---------------------------------------------------------------------------

  template<class TBaseIterator>
  class CNodeReference;
  //---------------------------------------------------------------------------
  // Declaration of CDataReference
  //---------------------------------------------------------------------------

  template<class TBaseIterator>
  class CDataReference : public TBaseIterator {
  public:
    using CBase = TBaseIterator;
    using reference = typename CBase::reference;
    using pointer = typename CBase::pointer;

    template<class TOtherBaseIterator>
    friend class CDataReference;
    template<class TOtherBaseIterator>
    CDataReference(const CDataReference<TOtherBaseIterator>& other);

    template<class TOtherBaseIterator>
    friend class CNodeReference;

    using CBase::CBase;
    CDataReference() = default;
    ~CDataReference() = default;
    CDataReference(const CDataReference& other) = default;
    CDataReference(CDataReference&& other) = default;
    CDataReference& operator=(const CDataReference& other) = default;
    CDataReference& operator=(CDataReference&& other) = default;

    reference operator*() const;
    pointer operator->() const;
  };
  //---------------------------------------------------------------------------
  // Declaration of CConstBasicIterator
  //---------------------------------------------------------------------------

  using CConstBasicIterator =
    CDataReference<CBaseIterator<CConstIteratorDefines>>;
  //---------------------------------------------------------------------------
  // Declaration of CBasicIterator
  //---------------------------------------------------------------------------

  using CBasicIterator = CDataReference<CBaseIterator<CIteratorDefines>>;
  //---------------------------------------------------------------------------
  // Declaration of CNodeReference
  //---------------------------------------------------------------------------

  template<class TBaseIterator>
  class CNodeReference : public TBaseIterator {
  public:
    using CBase = TBaseIterator;
    using CNodeRef = typename CBase::CNodeRef;
    using CNodePtr = typename CBase::CNode*;

    using CBase::CBase;
    CNodeReference() = default;
    ~CNodeReference() = default;
    CNodeReference(const CNodeReference& other) = default;
    CNodeReference(CNodeReference&& other) = default;
    CNodeReference& operator=(const CNodeReference& other) = default;
    CNodeReference& operator=(CNodeReference&& other) = default;

    CNodeReference(const CDataReference<TBaseIterator>& other);

    CNodeRef operator*() const;
    CNodePtr operator->() const;
  };
  //---------------------------------------------------------------------------
  // Declaration of CPreOrderLogic
  //---------------------------------------------------------------------------

  template<class TIteratorWithDereferencing>
  class CPreOrderLogic : public TIteratorWithDereferencing {
  public:
    using CBase = TIteratorWithDereferencing;
    using CHostTreePtr = typename CBase::CHostTreePtr;
    //using CNodePtr = typename CBase::CNode*;
    using CBase::CBase;
    CPreOrderLogic() = default;
    CPreOrderLogic(const CPreOrderLogic& other) = default;
    CPreOrderLogic(CPreOrderLogic&& other) = default;
    CPreOrderLogic& operator=(const CPreOrderLogic& other) = default;
    CPreOrderLogic& operator=(CPreOrderLogic&& other) = default;

    template<class TOtherIteratorWithDereferencing>
    bool operator<(const CPreOrderLogic<
                   TOtherIteratorWithDereferencing>& other) const;
    template<class TOtherIteratorWithDereferencing>
    bool operator<=(const CPreOrderLogic<
                    TOtherIteratorWithDereferencing>& other) const;
    template<class TOtherIteratorWithDereferencing>
    bool operator>(const CPreOrderLogic<
                   TOtherIteratorWithDereferencing>& other) const;
    template<class TOtherIteratorWithDereferencing>
    bool operator>=(const CPreOrderLogic<
                    TOtherIteratorWithDereferencing>& other) const;

  protected:
    void setToNext();
    void setToPrevious();
    void moveByOffset(int Offset);
    template<class TOtherIteratorWithDereferencing>
    int subtract(const CPreOrderLogic<
                 TOtherIteratorWithDereferencing>& other) const;
    ~CPreOrderLogic() = default;
  };
  template<class TIteratorWithDereferencing>
  friend class CPreOrderLogic;
  //---------------------------------------------------------------------------
  // Declaration of CLastSonLogic
  //---------------------------------------------------------------------------

  template<class TIteratorWithDereferencing>
  class CLastSonLogic : public TIteratorWithDereferencing {
  public:
    template<class TOtherIteratorWithDereferencing>
    friend class CLastSonLogic;

    using CBase = TIteratorWithDereferencing;
    using CHostTreePtr = typename CBase::CHostTreePtr;
    //using CNodePtr = typename CBase::CNode*;
    using CBase::CBase;
    CLastSonLogic() = default;
    CLastSonLogic(const CLastSonLogic& other) = default;
    CLastSonLogic(CLastSonLogic&& other) = default;
    CLastSonLogic& operator=(const CLastSonLogic& other) = default;
    CLastSonLogic& operator=(CLastSonLogic&& other) = default;

    template<class TOtherIteratorWithDereferencing>
    bool operator<(const CLastSonLogic<
                   TOtherIteratorWithDereferencing>& other) const;
    template<class TOtherIteratorWithDereferencing>
    bool operator<=(const CLastSonLogic<
                    TOtherIteratorWithDereferencing>& other) const;
    template<class TOtherIteratorWithDereferencing>
    bool operator>(const CLastSonLogic<
                   TOtherIteratorWithDereferencing>& other) const;
    template<class TOtherIteratorWithDereferencing>
    bool operator>=(const CLastSonLogic<
                    TOtherIteratorWithDereferencing>& other) const;
  protected:
    void setToNext();
    void setToPrevious();
    void moveByOffset(int Offset);
    template<class TOtherIteratorWithDereferencing>
    int subtract(const CLastSonLogic<
                 TOtherIteratorWithDereferencing>& other) const;

    ~CLastSonLogic() = default;
  };
  template<class TIteratorWithDereferencing>
  friend class CLastSonLogic;
  //---------------------------------------------------------------------------
  // Declaration of CSiblingLogic
  //---------------------------------------------------------------------------

  template<class TIteratorWithDereferencing>
  class CSiblingLogic : public TIteratorWithDereferencing {
  public:
    template<class TOtherIteratorWithDereferencing>
    friend class CSiblingLogic;

    using CBase = TIteratorWithDereferencing;
    using CHostTreePtr = typename CBase::CHostTreePtr;
    //using CNodePtr = typename CBase::CNode*;
    using CBase::CBase;
    CSiblingLogic() = default;
    CSiblingLogic(const CSiblingLogic& other) = default;
    CSiblingLogic(CSiblingLogic&& other) = default;
    CSiblingLogic& operator=(const CSiblingLogic& other) = default;
    CSiblingLogic& operator=(CSiblingLogic&& other) = default;

    template<class TOtherIteratorWithDereferencing>
    bool operator<(const CSiblingLogic<
                   TOtherIteratorWithDereferencing>& other) const;
    template<class TOtherIteratorWithDereferencing>
    bool operator<=(const CSiblingLogic<
                    TOtherIteratorWithDereferencing>& other) const;
    template<class TOtherIteratorWithDereferencing>
    bool operator>(const CSiblingLogic<
                   TOtherIteratorWithDereferencing>& other) const;
    template<class TOtherIteratorWithDereferencing>
    bool operator>=(const CSiblingLogic<
                    TOtherIteratorWithDereferencing>& other) const;
  protected:
    void setToNext();
    void setToPrevious();
    void moveByOffset(int Offset);
    template<class TOtherIteratorWithDereferencing>
    int subtract(const CSiblingLogic<
                 TOtherIteratorWithDereferencing>& other) const;
    ~CSiblingLogic() = default;
  };
  template<class TIteratorWithDereferencing>
  friend class CSiblingLogic;
  //---------------------------------------------------------------------------
  // Forward Declaration of CIteratorTemplate
  //---------------------------------------------------------------------------
  template <template<class> class TReferenceLogic,
            template<class> class TTravellingLogic,
            class TIteratorDefines>
  class CIteratorTemplate;
  //---------------------------------------------------------------------------
  // Declaration of CConstSiblingIterator
  //---------------------------------------------------------------------------
  using CConstSiblingIterator =
    CIteratorTemplate<CDataReference,
    CSiblingLogic,
    CConstIteratorDefines>;
  //---------------------------------------------------------------------------
  // Declaration of CSiblingIterator
  //---------------------------------------------------------------------------
  using CSiblingIterator =
    CIteratorTemplate<CDataReference,
    CSiblingLogic,
    CIteratorDefines>;
  //---------------------------------------------------------------------------
  // Declaration of CIteratorChildren
  //---------------------------------------------------------------------------

  template <class TIteratorWithTravellingLogic,
            class TIteratorDefines>
  class CIteratorChildren;
  //---------------------------------------------------------------------------

  template <class TIteratorWithTravellingLogic>
  class CIteratorChildren<TIteratorWithTravellingLogic, CIteratorDefines> :
    public TIteratorWithTravellingLogic {
  public:
    using CChildIterator = CSiblingIterator;
    using CBase = TIteratorWithTravellingLogic;
    using CBase::CBase;
  };
  //---------------------------------------------------------------------------

  template <class TIteratorWithTravellingLogic>
  class CIteratorChildren<TIteratorWithTravellingLogic, CConstIteratorDefines> :
    public TIteratorWithTravellingLogic {
  public:
    using CChildIterator = CConstSiblingIterator;
    using CBase = TIteratorWithTravellingLogic;
    using CBase::CBase;
  };
  //---------------------------------------------------------------------------
  // Declaration of CIteratorTemplate
  //---------------------------------------------------------------------------

  template <template<class> class TReferenceLogic,
            template<class> class TTravellingLogic,
            class TIteratorDefines>
  class CIteratorTemplate :
    public CIteratorChildren<
    TTravellingLogic<
    TReferenceLogic<
    CBaseIterator<
    TIteratorDefines>>>,
    TIteratorDefines> {
  public:
    friend CVTree;
    using CBase =
      CIteratorChildren<
      TTravellingLogic<
      TReferenceLogic<
      CBaseIterator<
      TIteratorDefines>>>,
      TIteratorDefines>;
    using CHostTreePtr = typename CBase::CHostTreePtr;
    using CNodePtr = typename CBase::CNode*;
    using difference_type = typename CBase::difference_type;
    using CChildIterator = typename CBase::CChildIterator;

    template <template<class> class TOtherReferenceLogic,
              template<class> class TOtherTravellingLogic,
              class TOtherIteratorDefines>
    friend class CIteratorTemplate;
    template <template<class> class TOtherReferenceLogic,
              template<class> class TOtherTravellingLogic,
              class TOtherIteratorDefines>
    CIteratorTemplate(
      const CIteratorTemplate<TOtherReferenceLogic,
      TOtherTravellingLogic,
      TOtherIteratorDefines>& other);
    using CBase::CBase;
    CIteratorTemplate() = default;
    CIteratorTemplate(const CIteratorTemplate&) = default;
    CIteratorTemplate(CIteratorTemplate&&) = default;
    CIteratorTemplate& operator=(const CIteratorTemplate&) = default;
    CIteratorTemplate& operator=(CIteratorTemplate&&) = default;
  protected:
    CIteratorTemplate(CHostTreePtr HostTree,
                      CNodeHandler Handler);
  public:
    CIteratorTemplate& operator++();
    CIteratorTemplate operator++(int);
    CIteratorTemplate& operator+=(difference_type Difference);
    CIteratorTemplate& operator--();
    CIteratorTemplate operator--(int);
    CIteratorTemplate& operator-=(difference_type Difference);

    template <template<class> class TOtherReferenceLogic,
              class TOtherIteratorDefines>
    difference_type
    operator-(const CIteratorTemplate<
              TOtherReferenceLogic,
              TTravellingLogic,
              TOtherIteratorDefines>& other) const;
    CChildIterator FirstChild() const;
    CChildIterator LastChild() const;
  };
  template <template<class> class TReferenceLogic,
            template<class> class TTravellingLogic,
            class TIteratorDefines>
  friend class CIteratorTemplate;
public:
  //---------------------------------------------------------------------------
  // Declaration of CConstPreOrderIterator
  //---------------------------------------------------------------------------
  using CConstPreOrderIterator =
    CIteratorTemplate<CDataReference,
    CPreOrderLogic,
    CConstIteratorDefines>;
  //---------------------------------------------------------------------------
  // Declaration of CPreOrderIterator
  //---------------------------------------------------------------------------
  using CPreOrderIterator =
    CIteratorTemplate<CDataReference,
    CPreOrderLogic,
    CIteratorDefines>;
  //---------------------------------------------------------------------------
  // Declaration of CConstLastSonIterator
  //---------------------------------------------------------------------------
  using CConstLastSonIterator =
    CIteratorTemplate<CDataReference,
    CLastSonLogic,
    CConstIteratorDefines>;
  //---------------------------------------------------------------------------
  // Declaration of CLastSonIterator
  //---------------------------------------------------------------------------
  using CLastSonIterator =
    CIteratorTemplate<CDataReference,
    CLastSonLogic,
    CIteratorDefines>;
  //---------------------------------------------------------------------------
  // Declaration of CConstLastSonNodIterator
  //---------------------------------------------------------------------------
  using CConstLastSonNodeIterator =
    CIteratorTemplate<CNodeReference,
    CLastSonLogic,
    CConstIteratorDefines>;
  //---------------------------------------------------------------------------
  CConstPreOrderIterator beginPreOrder() const;
  CConstPreOrderIterator endPreOrder() const;
  CConstPreOrderIterator cbeginPreOrder() const;
  CConstPreOrderIterator cendPreOrder() const;
  CPreOrderIterator beginPreOrder();
  CPreOrderIterator endPreOrder();

  CConstLastSonIterator beginLastSon() const;
  CConstLastSonIterator endLastSon() const;
  CConstLastSonIterator cbeginLastSon() const;
  CConstLastSonIterator cendLastSon() const;
  CLastSonIterator beginLastSon();
  CLastSonIterator endLastSon();
  //---------------------------------------------------------------------------
  // Declarations for STL compatability
  //---------------------------------------------------------------------------
  using const_iterator = CConstPreOrderIterator;
  using iterator = CPreOrderIterator;
  const_iterator begin() const;
  const_iterator end() const;
  const_iterator cbegin() const;
  const_iterator cend() const;
  iterator begin();
  iterator end();
  //---------------------------------------------------------------------------
protected:
  CNode& getRootNode();
  const CNode& getRootNode() const;
private:
  CVTreeBase TreeBase_;
};
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Definition of CVTreeNode
//---------------------------------------------------------------------------

template<class TType>
CVTreeNode<TType>::CVTreeNode ()
  : Data_(),
    Parent_(kRootNodeHandler),
    FirstChild_(kRootNodeHandler),
    LastChild_(kRootNodeHandler),
    PreviousSibling_(kRootNodeHandler),
    NextSibling_(kRootNodeHandler),
    NumberOfChildren_(0),
    DistanceToRoot_(0) {
}
//---------------------------------------------------------------------------

template<class TType>
CVTreeNode<TType>::CVTreeNode(const CData& Data,
                              CNodeHandler NodeHandler,
                              size_t DistanceToRoot)
  : Data_(Data),
    Parent_(NodeHandler),
    FirstChild_(NodeHandler),
    LastChild_(NodeHandler),
    PreviousSibling_(NodeHandler),
    NextSibling_(NodeHandler),
    NumberOfChildren_(0),
    DistanceToRoot_(DistanceToRoot) {
}
//---------------------------------------------------------------------------

template<class TType>
CVTreeNode<TType>::CVTreeNode(CData&& Data,
                              CNodeHandler NodeHandler,
                              size_t DistanceToRoot)
  : Data_(Data),
    Parent_(NodeHandler),
    FirstChild_(NodeHandler),
    LastChild_(NodeHandler),
    PreviousSibling_(NodeHandler),
    NextSibling_(NodeHandler),
    NumberOfChildren_(0),
    DistanceToRoot_(DistanceToRoot) {
}
//---------------------------------------------------------------------------

template<class TType>
bool CVTreeNode<TType>::isThereChild() const {
  return NumberOfChildren_ != 0;
}
//---------------------------------------------------------------------------
// Definition of CVTree
//---------------------------------------------------------------------------

template<class TType>
CVTree<TType>::CVTree(const CData& Data)
  : TreeBase_(1, CNode(Data, kRootNodeHandler, 0)) {
}
//---------------------------------------------------------------------------

template<class TType>
void CVTree<TType>::destroyExceptRoot() {
  if (empty())
    return;
  TreeBase_.resize(1);
  TreeBase_[kRootNodeHandler].FirstChild_ = kRootNodeHandler;
  TreeBase_[kRootNodeHandler].LastChild_ = kRootNodeHandler;
  TreeBase_[kRootNodeHandler].NumberOfChildren_ = 0;
  assert(TreeBase_[kRootNodeHandler].PreviousSibling_ == kRootNodeHandler);
  assert(TreeBase_[kRootNodeHandler].NextSibling_ == kRootNodeHandler);
}
//---------------------------------------------------------------------------

template<class TType>
bool CVTree<TType>::empty() const {
  return TreeBase_.empty();
}
//---------------------------------------------------------------------------

template<class TType>
size_t CVTree<TType>::size() const {
  return TreeBase_.size();
}
//---------------------------------------------------------------------------

template<class TType>
void CVTree<TType>::clear() {
  TreeBase_.clear();
}
//---------------------------------------------------------------------------

template<class TType>
typename CVTree<TType>::CConstPreOrderIterator
CVTree<TType>::beginPreOrder() const {
  return CConstPreOrderIterator(this, kRootNodeHandler);
}
//---------------------------------------------------------------------------

template<class TType>
typename CVTree<TType>::CConstPreOrderIterator
CVTree<TType>::endPreOrder() const {
  return CConstPreOrderIterator(this, size());
}
//---------------------------------------------------------------------------

template<class TType>
typename CVTree<TType>::CConstPreOrderIterator
CVTree<TType>::cbeginPreOrder() const {
  return beginPreOrder();
}
//---------------------------------------------------------------------------

template<class TType>
typename CVTree<TType>::CConstPreOrderIterator
CVTree<TType>::cendPreOrder() const {
  return endPreOrder();
}
//---------------------------------------------------------------------------

template<class TType>
typename CVTree<TType>::CPreOrderIterator
CVTree<TType>::beginPreOrder() {
  return CPreOrderIterator(this, kRootNodeHandler);
}
//---------------------------------------------------------------------------

template<class TType>
typename CVTree<TType>::CPreOrderIterator
CVTree<TType>::endPreOrder() {
  return CPreOrderIterator(this, size());
}
//---------------------------------------------------------------------------

template<class TType>
typename CVTree<TType>::CConstLastSonIterator
CVTree<TType>::beginLastSon() const {
  return CConstLastSonIterator(this, kRootNodeHandler);
}
//---------------------------------------------------------------------------

template<class TType>
typename CVTree<TType>::CConstLastSonIterator
CVTree<TType>::endLastSon() const {
  return CConstLastSonIterator(this, size());
}
//---------------------------------------------------------------------------

template<class TType>
typename CVTree<TType>::CConstLastSonIterator
CVTree<TType>::cbeginLastSon() const {
  return beginLastSon();
}
//---------------------------------------------------------------------------

template<class TType>
typename CVTree<TType>::CConstLastSonIterator
CVTree<TType>::cendLastSon() const {
  return endLastSon();
}
//---------------------------------------------------------------------------

template<class TType>
typename CVTree<TType>::CLastSonIterator
CVTree<TType>::beginLastSon() {
  return CLastSonIterator(this, kRootNodeHandler);
}
//---------------------------------------------------------------------------

template<class TType>
typename CVTree<TType>::CLastSonIterator
CVTree<TType>::endLastSon() {
  return CLastSonIterator(this, size());
}
//---------------------------------------------------------------------------

template<class TType>
typename CVTree<TType>::const_iterator
CVTree<TType>::begin() const {
  return beginPreOrder();
}
//---------------------------------------------------------------------------

template<class TType>
typename CVTree<TType>::const_iterator
CVTree<TType>::end() const {
  return endPreOrder();
}
//---------------------------------------------------------------------------

template<class TType>
typename CVTree<TType>::const_iterator
CVTree<TType>::cbegin() const {
  return begin();
}
//---------------------------------------------------------------------------

template<class TType>
typename CVTree<TType>::const_iterator
CVTree<TType>::cend() const {
  return end();
}
//---------------------------------------------------------------------------

template<class TType>
typename CVTree<TType>::iterator
CVTree<TType>::begin() {
  return beginPreOrder();
}
//---------------------------------------------------------------------------

template<class TType>
typename CVTree<TType>::iterator
CVTree<TType>::end() {
  return endPreOrder();
}
//---------------------------------------------------------------------------

template<class TType>
typename CVTree<TType>::CNode&
CVTree<TType>::getRootNode() {
  return TreeBase_[kRootNodeHandler];
}
//---------------------------------------------------------------------------

template<class TType>
const typename CVTree<TType>::CNode&
CVTree<TType>::
getRootNode() const {
  return TreeBase_[kRootNodeHandler];
}
//---------------------------------------------------------------------------
// Definition of CBaseIterator
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
CBaseIterator()
  : Host_(nullptr),
    Current_(0) {
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
CBaseIterator(CHostTreePtr HostTree,
              CNodeHandler Current)
  : Host_(HostTree),
    Current_(Current) {
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
CBaseIterator(const CBaseIterator& other)
  : Host_(other.Host_),
    Current_(other.Current_) {
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
CBaseIterator(CBaseIterator&& other)
  : Host_(other.Host_),
    Current_(other.Current_) {
  other.Host_ = nullptr;
  other.Current_ = 0;
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
typename CVTree<TType>::template CBaseIterator<TIteratorDefines>&
CVTree<TType>::CBaseIterator<TIteratorDefines>::
operator=(const CBaseIterator& other) {
  return *this = CBaseIterator(other);
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
typename CVTree<TType>::template CBaseIterator<TIteratorDefines>&
CVTree<TType>::CBaseIterator<TIteratorDefines>::
operator=(CBaseIterator&& other) {
  Host_ = other.Host_;
  Current_ = other.Current_;
  other.Host_ = nullptr;
  other.Current_ = 0;
  return *this;
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
template<class TOtherIteratorDefines>
bool
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
operator==(const CBaseIterator<TOtherIteratorDefines>& Iterator) const {
  return  Host_ == Iterator.Host_ && Current_ == Iterator.Current_;
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
template<class TOtherIteratorDefines>
bool
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
operator!=(const CBaseIterator<TOtherIteratorDefines>& Iterator) const {
  return !(*this == Iterator);
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
bool
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
isDefined() const {
  return isHostDefined() && isCurrentInDefinedRange();
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
bool
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
isRoot() const {
  assert( !isHostDefined() || (
            Current_ != kRootNodeHandler ||
            Current_ == getParentHandler()));
  return isHostDefined() && Current_ == kRootNodeHandler;
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
bool
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
isLeaf() const {
  return isHostDefined() && !getCurrentNode().isThereChild();
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
bool
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
isThereParent() const {
  return isHostDefined() && Current_ != getParentHandler();
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
bool
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
isThereChild() const {
  return isHostDefined() && getCurrentNode().isThereChild();
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
bool
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
isThereNextSibling() const {
  return isHostDefined() && Current_ != getNextSiblingHandler();
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
bool
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
isTherePreviousSibling() const {
  return isHostDefined() && Current_ != getPreviousSiblingHandler();
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
size_t
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
getNumberOfChildren() const {
  if (isDefined())
    return getCurrentNode().NumberOfChildren_;
  return 0;
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
size_t
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
getSizeOfSubTree() const {
  if (!isDefined())
    return 0;
  return getSubTreeEndHandler() - Current_;
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
size_t
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
getNumberOfSiblings() const {
  if (!isThereParent())
    return 0;
  return getParentNode().NumberOfChildren_ - 1;
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
size_t
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
getLengthOfSubTree() const {
  if (!isDefined())
    return 0;
  CNodeHandler EndHandler = getSubTreeEndHandler();
  size_t MaxDistanceToRoot = 0;
  for(CNodeHandler Current = Current_; Current != EndHandler; ++Current)
    MaxDistanceToRoot = std::max( MaxDistanceToRoot,
                                  getNode(Current).DistanceToRoot_);
  return MaxDistanceToRoot - getCurrentNode().DistanceToRoot_ + 1;
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
size_t
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
getNumberOfLeaves() const {
  if (!isDefined())
    return 0;
  CNodeHandler EndHandler = getSubTreeEndHandler();
  size_t NumberOfLeaves = 0;
  for(CNodeHandler Current = Current_; Current != EndHandler; ++Current)
    if (!getNode(Current).isThereChild())
      ++NumberOfLeaves;
  assert(NumberOfLeaves > 0);
  return NumberOfLeaves;
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
size_t
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
getDistanceToRoot() const {
  if (!isDefined())
    return 0;
  return getCurrentNode().DistanceToRoot_;
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
size_t
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
getHostSize() const {
  if (!isDefined())
    return 0;
  return Host_->size();
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
void
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
setToParent() {
  assert(isThereParent());
  Current_ = getParentHandler();
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
void
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
setToFirstChild() {
  assert(isThereChild());
  Current_ = getFirstChildHandler();
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
void
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
setToLastChild() {
  assert(isThereChild());
  Current_ = getLastChildHandler();
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
void
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
setToNextSibling() {
  assert(isThereNextSibling());
  Current_ = getNextSiblingHandler();
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
void
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
setToPreviousSibling() {
  assert(isTherePreviousSibling());
  Current_ = getPreviousSiblingHandler();
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
void
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
addLastChild(const value_type& NodeData) {
  assert(!isThereNextSibling());
  CNodeHandler NewNodePosition = getHostSize();
  (Host_->TreeBase_).emplace_back(
    NodeData, NewNodePosition, getDistanceToRoot() + 1);
  if(isLeaf()) {
    getCurrentNode().FirstChild_ = NewNodePosition;
    getCurrentNode().LastChild_ = NewNodePosition;
    getNode(NewNodePosition).Parent_ = Current_;
  } else {
    getLastChildNode().NextSibling_ = NewNodePosition;
    getNode(NewNodePosition).PreviousSibling_ = getLastChildHandler();
    getNode(NewNodePosition).Parent_ = Current_;
    getCurrentNode().LastChild_ = NewNodePosition;
  }
  ++(getCurrentNode().NumberOfChildren_);
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
void
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
addLastChild(value_type&& NodeData) {
  assert(!isThereNextSibling());
  CNodeHandler NewNodePosition = getHostSize();
  (Host_->TreeBase_).emplace_back(
    NodeData, NewNodePosition, getDistanceToRoot() + 1);
  if(isLeaf()) {
    getCurrentNode().FirstChild_ = NewNodePosition;
    getCurrentNode().LastChild_ = NewNodePosition;
    getNode(NewNodePosition).Parent_ = Current_;
  } else {
    getLastChildNode().NextSibling_ = NewNodePosition;
    getNode(NewNodePosition).PreviousSibling_ = getLastChildHandler();
    getNode(NewNodePosition).Parent_ = Current_;
    getCurrentNode().LastChild_ = NewNodePosition;
  }
  ++(getCurrentNode().NumberOfChildren_);
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
void
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
changeHost(CHostTreePtr Host) {
  Host_ = Host;
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
bool
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
isHostDefined() const {
  return Host_ != nullptr;
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
bool
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
isCurrentInFullRange() const {
  return Current_ <= Host_->size();
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
bool
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
isCurrentInDefinedRange() const {
  return Current_ < Host_->size();
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
typename CVTree<TType>::
template CBaseIterator<TIteratorDefines>::
CNodeHandler
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
getParentHandler() const {
  return getCurrentNode().Parent_;
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
typename CVTree<TType>::
template CBaseIterator<TIteratorDefines>::
CNodeHandler
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
getFirstChildHandler() const {
  return getCurrentNode().FirstChild_;
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
typename CVTree<TType>::
template CBaseIterator<TIteratorDefines>::
CNodeHandler
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
getLastChildHandler() const {
  return getCurrentNode().LastChild_;
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
typename CVTree<TType>::
template CBaseIterator<TIteratorDefines>::
CNodeHandler
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
getPreviousSiblingHandler() const {
  return getCurrentNode().PreviousSibling_;
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
typename CVTree<TType>::
template CBaseIterator<TIteratorDefines>::
CNodeHandler
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
getNextSiblingHandler() const {
  return getCurrentNode().NextSibling_;
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
typename CVTree<TType>::
template CBaseIterator<TIteratorDefines>::
CNodeHandler
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
getSubTreeEndHandler() const {
  CBaseIterator Current (*this);
  while (!Current.isRoot() && !Current.isThereNextSibling())
    Current.setToParent();
  if (Current.isThereNextSibling())
    return Current.getNextSiblingHandler();
  return getHostSize();
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
typename CVTree<TType>::
template CBaseIterator<TIteratorDefines>::
CNode&
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
getNode(const CNodeHandler& Handler) {
  return (Host_->TreeBase_)[Handler];
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
const typename CVTree<TType>::
template CBaseIterator<TIteratorDefines>::
CNode&
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
getNode(const CNodeHandler& Handler) const {
  return (Host_->TreeBase_)[Handler];
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
typename CVTree<TType>::
template CBaseIterator<TIteratorDefines>::
CNode&
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
getCurrentNode() {
  return getNode(Current_);
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
const typename CVTree<TType>::
template CBaseIterator<TIteratorDefines>::
CNode&
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
getCurrentNode() const {
  return getNode(Current_);
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
typename CVTree<TType>::
template CBaseIterator<TIteratorDefines>::
CNode&
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
getParentNode() {
  return getNode(getParentHandler());
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
const typename CVTree<TType>::
template CBaseIterator<TIteratorDefines>::
CNode&
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
getParentNode() const {
  return getNode(getParentHandler());
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
typename CVTree<TType>::
template CBaseIterator<TIteratorDefines>::
CNode&
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
getFirstChildNode() {
  return getNode(getFirstChildHandler());
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
const typename CVTree<TType>::
template CBaseIterator<TIteratorDefines>::
CNode&
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
getFirstChildNode() const {
  return getNode(getFirstChildHandler());
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
typename CVTree<TType>::
template CBaseIterator<TIteratorDefines>::
CNode&
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
getLastChildNode() {
  return getNode(getLastChildHandler());
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
const typename CVTree<TType>::
template CBaseIterator<TIteratorDefines>::
CNode&
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
getLastChildNode() const {
  return getNode(getLastChildHandler());
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
typename CVTree<TType>::
template CBaseIterator<TIteratorDefines>::
CNode&
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
getPreviousSiblingNode() {
  return getNode(getPreviousSiblingHandler());
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
const typename CVTree<TType>::
template CBaseIterator<TIteratorDefines>::
CNode&
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
getPreviousSiblingNode() const {
  return getNode(getPreviousSiblingHandler());
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
typename CVTree<TType>::
template CBaseIterator<TIteratorDefines>::
CNode&
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
getNextSiblingNode() {
  return getNode(getNextSiblingHandler());
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
const typename CVTree<TType>::
template CBaseIterator<TIteratorDefines>::
CNode&
CVTree<TType>::
CBaseIterator<TIteratorDefines>::
getNextSiblingNode() const {
  return getNode(getNextSiblingHandler());
}
//---------------------------------------------------------------------------
// Definition of CDataReference
//---------------------------------------------------------------------------

template<class TType>
template<class TBaseIterator>
template<class TOtherBaseIterator>
CVTree<TType>::
CDataReference<TBaseIterator>::
CDataReference(const CDataReference<TOtherBaseIterator>& other)
  : CBase(other.Host_, other.Current_) {
}
//---------------------------------------------------------------------------

template<class TType>
template<class TBaseIterator>
typename
CVTree<TType>::
template
CDataReference<TBaseIterator>::
reference
CVTree<TType>::
CDataReference<TBaseIterator>::
operator*() const {
  return (CBase::Host_->TreeBase_)[CBase::Current_].Data_;
}
//---------------------------------------------------------------------------

template<class TType>
template<class TBaseIterator>
typename
CVTree<TType>::
template
CDataReference<TBaseIterator>::
pointer
CVTree<TType>::
CDataReference<TBaseIterator>::
operator->() const {
  return &((CBase::Host_->TreeBase_)[CBase::Current_].Data_);
}
//---------------------------------------------------------------------------
// Definition of CNodeReference
//---------------------------------------------------------------------------

template<class TType>
template<class TBaseIterator>
CVTree<TType>::
CNodeReference<TBaseIterator>::
CNodeReference(const CDataReference<TBaseIterator>& other)
  : CBase(other.Host_, other.Current_) {
}
//---------------------------------------------------------------------------

template<class TType>
template<class TBaseIterator>
typename
CVTree<TType>::
template
CNodeReference<TBaseIterator>::
CNodeRef
CVTree<TType>::
CNodeReference<TBaseIterator>::
operator*() const {
  return (CBase::Host_->TreeBase_)[CBase::Current_];
}
//---------------------------------------------------------------------------

template<class TType>
template<class TBaseIterator>
typename
CVTree<TType>::
template
CNodeReference<TBaseIterator>::
CNodePtr
CVTree<TType>::
CNodeReference<TBaseIterator>::
operator->() const {
  return &((CBase::Host_->TreeBase_)[CBase::Current_]);
}
//---------------------------------------------------------------------------
// Definition of CPreOrderLogic
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorWithDereferencing>
void
CVTree<TType>::
CPreOrderLogic<TIteratorWithDereferencing>::
setToNext() {
  assert(CBase::isHostDefined());
  ++CBase::Current_;
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorWithDereferencing>
void
CVTree<TType>::
CPreOrderLogic<TIteratorWithDereferencing>::
setToPrevious() {
  assert(CBase::isHostDefined());
  --CBase::Current_;
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorWithDereferencing>
void
CVTree<TType>::
CPreOrderLogic<TIteratorWithDereferencing>::
moveByOffset(int Offset) {
  assert(CBase::isHostDefined());
  CBase::Current_ += Offset;
  assert(CBase::isCurrentInFullRange());
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorWithDereferencing>
template<class TOtherIteratorWithDereferencing>
int
CVTree<TType>::
CPreOrderLogic<TIteratorWithDereferencing>::
subtract(const CPreOrderLogic<
         TOtherIteratorWithDereferencing>& other) const {
  assert(CBase::Host_ == other.Host_);
  if(!CBase::isHostDefined())
    return 0;
  return CBase::Current_ - other.Current_;
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorWithDereferencing>
template<class TOtherIteratorWithDereferencing>
bool
CVTree<TType>::
CPreOrderLogic<TIteratorWithDereferencing>::
operator<(const CPreOrderLogic<
          TOtherIteratorWithDereferencing>& other) const {
  assert(CBase::Host_ == other.Host_);
  if (!CBase::isHostDefined())
    return false;
  return CBase::Current_ < other.Current_;
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorWithDereferencing>
template<class TOtherIteratorWithDereferencing>
bool
CVTree<TType>::
CPreOrderLogic<TIteratorWithDereferencing>::
operator<=(const CPreOrderLogic<
           TOtherIteratorWithDereferencing>& other) const {
  return !(other < *this);
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorWithDereferencing>
template<class TOtherIteratorWithDereferencing>
bool
CVTree<TType>::
CPreOrderLogic<TIteratorWithDereferencing>::
operator>(const CPreOrderLogic<
          TOtherIteratorWithDereferencing>& other) const {
  return other < *this;
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorWithDereferencing>
template<class TOtherIteratorWithDereferencing>
bool
CVTree<TType>::
CPreOrderLogic<TIteratorWithDereferencing>::
operator>=(const CPreOrderLogic<
           TOtherIteratorWithDereferencing>& other) const {
  return !(*this < other);
}
//---------------------------------------------------------------------------
// Definition of CLastSonLogic
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
void
CVTree<TType>::
CLastSonLogic<TIteratorDefines>::
setToNext() {
  assert(CBase::isHostDefined());
  if (CBase::isThereChild())
    CBase::setToLastChild();
  else
    CBase::Current_ = CBase::getHostSize();
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
void
CVTree<TType>::
CLastSonLogic<TIteratorDefines>::
setToPrevious() {
  assert(CBase::isHostDefined());
  if (CBase::isCurrentInDefinedRange()) {
    assert(CBase::isThereParent());
    CBase::setToParent();
  } else {
    assert(CBase::Current_ > 0);
    --(CBase::Current_);
  }
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
void
CVTree<TType>::
CLastSonLogic<TIteratorDefines>::
moveByOffset(int Offset) {
  assert(CBase::isHostDefined());
  while (Offset > 0) {
    --Offset;
    setToNext();
  }
  while (Offset < 0) {
    ++Offset;
    setToPrevious();
  }
  assert(CBase::isCurrentInFullRange());
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
template<class TOtherIteratorWithDereferencing>
int
CVTree<TType>::
CLastSonLogic<TIteratorDefines>::
subtract(const CLastSonLogic<
         TOtherIteratorWithDereferencing>& other) const {
  assert(CBase::Host_ == other.Host_);
  if (!CBase::isHostDefined())
    return 0;
  int difference = 0;
  CLastSonLogic current = *this;
  while (current < other) {
    current.setToNext();
    ++difference;
  }
  while (current > other) {
    current.setToPrevious();
    ++difference;
  }
  return difference;
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
template<class TOtherIteratorWithDereferencing>
bool
CVTree<TType>::
CLastSonLogic<TIteratorDefines>::
operator<(const CLastSonLogic<
          TOtherIteratorWithDereferencing>& other) const {
  assert(CBase::Host_ == other.Host_);
  if (!CBase::isHostDefined())
    return false;
  return CBase::Current_ < other.Current_;
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
template<class TOtherIteratorWithDereferencing>
bool
CVTree<TType>::
CLastSonLogic<TIteratorDefines>::
operator<=(const CLastSonLogic<
           TOtherIteratorWithDereferencing>& other) const {
  return !(other < *this);
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
template<class TOtherIteratorWithDereferencing>
bool
CVTree<TType>::
CLastSonLogic<TIteratorDefines>::
operator>(const CLastSonLogic<
          TOtherIteratorWithDereferencing>& other) const {
  return other < *this;
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
template<class TOtherIteratorWithDereferencing>
bool
CVTree<TType>::
CLastSonLogic<TIteratorDefines>::
operator>=(const CLastSonLogic<
           TOtherIteratorWithDereferencing>& other) const {
  return !(*this < other);
}
//---------------------------------------------------------------------------
// Definition of CSiblingLogic
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
void
CVTree<TType>::
CSiblingLogic<TIteratorDefines>::
setToNext() {
  assert(CBase::isThereNextSibling());
  CBase::setToNextSibling();
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
void
CVTree<TType>::
CSiblingLogic<TIteratorDefines>::
setToPrevious() {
  assert(CBase::isTherePreviousSibling());
  CBase::setToPreviousSibling();
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
void
CVTree<TType>::
CSiblingLogic<TIteratorDefines>::
moveByOffset(int Offset) {
  assert(CBase::isHostDefined());
  while (Offset > 0) {
    --Offset;
    setToNext();
  }
  while (Offset < 0) {
    ++Offset;
    setToPrevious();
  }
  assert(CBase::isCurrentInFullRange());
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorDefines>
template<class TOtherIteratorWithDereferencing>
int
CVTree<TType>::
CSiblingLogic<TIteratorDefines>::
subtract(const CSiblingLogic<
         TOtherIteratorWithDereferencing>& other) const {
  assert(CBase::Host_ == other.Host_);
  if (!CBase::isHostDefined())
    return 0;
  int difference = 0;
  auto current = *this;
  while (current < other) {
    current.setToNext();
    ++difference;
  }
  while (current > other) {
    current.setToPrevious();;
    ++difference;
  }
  return difference;
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorWithDereferencing>
template<class TOtherIteratorWithDereferencing>
bool
CVTree<TType>::
CSiblingLogic<TIteratorWithDereferencing>::
operator<(const CSiblingLogic<
          TOtherIteratorWithDereferencing>& other) const {
  assert(CBase::Host_ == other.Host_);
  if (!CBase::isHostDefined())
    return false;
  return CBase::Current_ < other.Current_;
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorWithDereferencing>
template<class TOtherIteratorWithDereferencing>
bool
CVTree<TType>::
CSiblingLogic<TIteratorWithDereferencing>::
operator<=(const CSiblingLogic<
           TOtherIteratorWithDereferencing>& other) const {
  return !(other < *this);
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorWithDereferencing>
template<class TOtherIteratorWithDereferencing>
bool
CVTree<TType>::
CSiblingLogic<TIteratorWithDereferencing>::
operator>(const CSiblingLogic<
          TOtherIteratorWithDereferencing>& other) const {
  return other < *this;
}
//---------------------------------------------------------------------------

template<class TType>
template<class TIteratorWithDereferencing>
template<class TOtherIteratorWithDereferencing>
bool
CVTree<TType>::
CSiblingLogic<TIteratorWithDereferencing>::
operator>=(const CSiblingLogic<
           TOtherIteratorWithDereferencing>& other) const {
  return !(*this < other);
}
//---------------------------------------------------------------------------
// Definition of CIteratorTemplate
//---------------------------------------------------------------------------

template<class TType>
template <template<class> class TReferenceLogic,
          template<class> class TTravellingLogic,
          class TIteratorDefines>
template <template<class> class TOtherReferenceLogic,
          template<class> class TOtherTravellingLogic,
          class TOtherIteratorDefines>
CVTree<TType>::
CIteratorTemplate<TReferenceLogic,
                  TTravellingLogic,
                  TIteratorDefines>::
                  CIteratorTemplate(
                    const CIteratorTemplate<TOtherReferenceLogic,
                    TOtherTravellingLogic,
                    TOtherIteratorDefines>& other)
                    : CBase(other.Host_, other.Current_) {
}
//---------------------------------------------------------------------------

template<class TType>
template <template<class> class TReferenceLogic,
          template<class> class TTravellingLogic,
          class TIteratorDefines>
CVTree<TType>::
CIteratorTemplate<TReferenceLogic,
                  TTravellingLogic,
                  TIteratorDefines>::
                  CIteratorTemplate(CHostTreePtr HostTree,
                                    CNodeHandler Handler)
                    : CBase(HostTree, Handler) {
}
//---------------------------------------------------------------------------

template<class TType>
template <template<class> class TReferenceLogic,
          template<class> class TTravellingLogic,
          class TIteratorDefines>
typename
CVTree<TType>::template
CIteratorTemplate<TReferenceLogic,
                  TTravellingLogic,
                  TIteratorDefines>&
CVTree<TType>::
CIteratorTemplate<TReferenceLogic,
                  TTravellingLogic,
                  TIteratorDefines>::
operator++() {
  CBase::setToNext();
  return *this;
}
//---------------------------------------------------------------------------

template<class TType>
template <template<class> class TReferenceLogic,
          template<class> class TTravellingLogic,
          class TIteratorDefines>
typename
CVTree<TType>::template
CIteratorTemplate<TReferenceLogic,
                  TTravellingLogic,
                  TIteratorDefines>
CVTree<TType>::
CIteratorTemplate<TReferenceLogic,
                  TTravellingLogic,
                  TIteratorDefines>::
operator++(int) {
  CIteratorTemplate temp = *this;
  ++*this;
  return temp;
}
//---------------------------------------------------------------------------

template<class TType>
template <template<class> class TReferenceLogic,
          template<class> class TTravellingLogic,
          class TIteratorDefines>
typename
CVTree<TType>::template
CIteratorTemplate<TReferenceLogic,
                  TTravellingLogic,
                  TIteratorDefines>&
CVTree<TType>::
CIteratorTemplate<TReferenceLogic,
                  TTravellingLogic,
                  TIteratorDefines>::
operator+=(difference_type Difference) {
  CBase::moveByOffset(Difference);
  return *this;
}
//---------------------------------------------------------------------------

template<class TType>
template <template<class> class TReferenceLogic,
          template<class> class TTravellingLogic,
          class TIteratorDefines>
typename
CVTree<TType>::template
CIteratorTemplate<TReferenceLogic,
                  TTravellingLogic,
                  TIteratorDefines>&
CVTree<TType>::
CIteratorTemplate<TReferenceLogic,
                  TTravellingLogic,
                  TIteratorDefines>::
operator--() {
  CBase::setToPrevious();
  return *this;
}
//---------------------------------------------------------------------------

template<class TType>
template <template<class> class TReferenceLogic,
          template<class> class TTravellingLogic,
          class TIteratorDefines>
typename
CVTree<TType>::template
CIteratorTemplate<TReferenceLogic,
                  TTravellingLogic,
                  TIteratorDefines>
CVTree<TType>::
CIteratorTemplate<TReferenceLogic,
                  TTravellingLogic,
                  TIteratorDefines>::
operator--(int) {
  CIteratorTemplate temp = *this;
  --*this;
  return temp;
}
//---------------------------------------------------------------------------

template<class TType>
template <template<class> class TReferenceLogic,
          template<class> class TTravellingLogic,
          class TIteratorDefines>
typename
CVTree<TType>::template
CIteratorTemplate<TReferenceLogic,
                  TTravellingLogic,
                  TIteratorDefines>&
CVTree<TType>::
CIteratorTemplate<TReferenceLogic,
                  TTravellingLogic,
                  TIteratorDefines>::
operator-=(difference_type Difference) {
  CBase::moveByOffset(-Difference);
  return *this;
}
//---------------------------------------------------------------------------

template<class TType>
template <template<class> class TReferenceLogic,
          template<class> class TTravellingLogic,
          class TIteratorDefines>
template <template<class> class TOtherReferenceLogic,
          class TOtherIteratorDefines>
typename
CVTree<TType>::template
CIteratorTemplate<TReferenceLogic,
                  TTravellingLogic,
                  TIteratorDefines>::
difference_type
CVTree<TType>::
CIteratorTemplate<TReferenceLogic,
                  TTravellingLogic,
                  TIteratorDefines>::
                  operator-(const CIteratorTemplate<
                            TOtherReferenceLogic,
                            TTravellingLogic,
TOtherIteratorDefines>& other) const {
  return CBase::subtract(other);
}
//---------------------------------------------------------------------------

template<class TType>
template <template<class> class TReferenceLogic,
          template<class> class TTravellingLogic,
          class TIteratorDefines>
typename
CVTree<TType>::template
CIteratorTemplate<TReferenceLogic,
                  TTravellingLogic,
                  TIteratorDefines>::
CChildIterator
CVTree<TType>::
CIteratorTemplate<TReferenceLogic,
                  TTravellingLogic,
                  TIteratorDefines>::
FirstChild() const {
  return CChildIterator(CBase::Host_, CBase::getFirstChildHandler());
}
//---------------------------------------------------------------------------

template<class TType>
template <template<class> class TReferenceLogic,
          template<class> class TTravellingLogic,
          class TIteratorDefines>
typename
CVTree<TType>::template
CIteratorTemplate<TReferenceLogic,
                  TTravellingLogic,
                  TIteratorDefines>::
CChildIterator
CVTree<TType>::
CIteratorTemplate<TReferenceLogic,
                  TTravellingLogic,
                  TIteratorDefines>::
LastChild() const {
  return CChildIterator(CBase::Host_, CBase::getLastChildHandler());
}
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
#endif // VTREE_H
